#include "KisoRenderer.h"

using namespace std;

KisoRenderer::KisoRenderer()
{
}

cairo_matrix_t KisoRenderer::buildTransform( YAML::Node& layout )
{
}

void KisoRenderer::queueRender( cairo_t* cr, KisoApp* app)
{
  YAML::Node presentation = YAML::Clone(*(app->presentation()));
	YAML::Node style = presentation["style"];
	YAML::Node layout = presentation["layout"];
	drawNode( cr, *(app->structure()), style, layout );
}

YAML::Node KisoRenderer::mergeNodes(YAML::Node base, YAML::Node overlay1, YAML::Node overlay2)
{
	YAML::Node output = YAML::Clone(base);
  output |= overlay1;
	output |= overlay2;
	
	return output;
}

void KisoRenderer::drawBorder( cairo_t* cr,  YAML::Node& style, YAML::Node& layout )
{
  double width   = style["border-width"].as<double>();
  vec4d color    = style["border-color"].as<vec4d>();
  vec3d position = layout["position"].as<vec3d>();
  vec2d size     = layout["size"].as<vec2d>();
  
  cairo_set_source_rgba( cr, color.r, color.g, color.b, color.a );
  cairo_set_line_width( cr, width );
  cairo_rectangle( cr, position.x, position.y, size.x, size.y );
  cairo_stroke( cr );
}

void KisoRenderer::drawBackground( cairo_t* cr,  YAML::Node& style, YAML::Node& layout )
{
  vec4d color     = style["background-color"].as<vec4d>();
  string filename = style["background-image"].as<string>();
  vec2d size      = layout["size"].as<vec2d>();
  vec3d position  = layout["position"].as<vec3d>();
  
  if (filename != "") {
    cairo_surface_t *img = cairo_image_surface_create_from_png( filename.c_str() );
    cairo_save( cr );
    cairo_translate( cr, position.x, position.y );
    cairo_set_source_surface( cr, img, size.x, size.y );
    cairo_paint( cr );
    cairo_surface_destroy( img );
    cairo_restore( cr );
  } else {
    cairo_set_source_rgba( cr, color.r, color.g, color.b, color.a );
    cairo_rectangle( cr, position.x, position.y, size.x, size.y );
    cairo_fill( cr );
  }
}

YAML::Node KisoRenderer::computeLayout( string name, YAML::Node node, YAML::Node& parent )
{
  YAML::Node localLayout = node["layout"];
  YAML::Node childLayout = parent["children"][name]["layout"];
  YAML::Node globalLayout = m_presentation[name]["layout"];
  return mergeNodes( globalLayout, childLayout, localLayout );
}

YAML::Node KisoRenderer::computeStyle( string name,YAML::Node node, YAML::Node& parent )
{
  // The rules of styling/layout are as follows:
  // 1. Locally set properties
  // 2. Properties in the parent's 'children' map wins.
  // 3. Global properties
  YAML::Node localStyle = node["style"];
  YAML::Node childStyle = parent["children"][name]["style"];
  YAML::Node globalStyle = m_presentation[name]["style"];
  return mergeNodes( globalStyle, childStyle, localStyle );
}

void KisoRenderer::drawGridChildren( cairo_t* cr,  YAML::Node& node, YAML::Node& layout ) 
{
  for ( YAML::const_iterator it = node.begin(); it!=node.end(); ++it )
  {
    string name = it->first.as<std::string>();
    if ( name != "style" && name != "layout" )
    {
      YAML::Node childLayout = computeLayout( name, *it, node );
      vec2i gridPosition = childLayout["grid-position"].as<vec2i>();
      vec2d newPosition(0,0);
      for (int i = 0; i < gridPosition.x; i++) {
        newPosition.x += layout["columns"][i].as<double>();
      }
      for (int i = 0; i < gridPosition.y; i++) {
        newPosition.y += layout["rows"][i].as<double>();
      }
      childLayout["position"] = newPosition;
      
      YAML::Node style = computeStyle( name, *it, node );
    	YAML::Node child = *it;
      drawNode( cr, child, style, childLayout );
    }
  }
}

void KisoRenderer::drawFillChildren( cairo_t* cr,  YAML::Node& node, YAML::Node& layout ) 
{
  vec2d pos( 0, 0 );
  double rowHeight = 0;
  vec2d parentSize = layout["size"].as<vec2d>();
  
  for ( YAML::const_iterator it = node.begin(); it!=node.end(); ++it )
  {
    string name = it->first.as<std::string>();
    
    if ( name != "style" && name != "layout" )
    {
      YAML::Node childLayout = computeLayout( name, *it, node );
      YAML::Node style = computeStyle( name, *it, node );
      
      vec2d size = childLayout["size"].as<vec2d>();
      
      if (pos.x + size.x > parentSize.x)
      {
        pos.y += rowHeight;
        pos.x = 0;
      } 
      else
      {
        if ( size.y > rowHeight )
        {
          rowHeight = size.y;
        }
      
        childLayout["position"] = vec2d( pos.x, pos.y );
        pos.x += size.x;
      }
      YAML::Node child = *it;
      drawNode( cr, child, style, childLayout );
    }
  }
}

void KisoRenderer::draw2DChildren( cairo_t* cr, YAML::Node& node ) 
{
  for ( YAML::const_iterator it = node.begin(); it!=node.end(); ++it )
  {
    string name = it->first.as<std::string>();
    if ( name != "style" && name != "layout" )
    {
      YAML::Node childLayout = computeLayout( name, *it, node );
      YAML::Node style = computeStyle( name, *it, node );
			YAML::Node child = *it;
      drawNode( cr, child, style, childLayout );
    }
  }
}


void KisoRenderer::drawNode( cairo_t* cr, YAML::Node& node, YAML::Node& style, YAML::Node& layout ) 
{

  // 0. Push matrix
  cairo_save( cr );
  
  // 1. Apply transform
  cairo_matrix_t mat = buildTransform( layout );
  cairo_set_matrix( cr, &mat );

  // 2. Draw shadow
  //drawShadow( cr, style, layout );
  
  // 3. Draw background
  drawBackground ( cr, style, layout );
  
  // 4. Draw border
  drawBorder ( cr, style, layout ); 
    
  //5. Draw Children
  string type = layout["type"].as<string>();
  if ( type == "2D" )
  {
    draw2DChildren( cr, node );
  }
  else if ( type == "fill" )
  {
    drawFillChildren( cr, node, layout );
  }
  else if ( type == "grid" )
  {
    drawGridChildren( cr, node, layout );
  }
  
  // 6. Draw text if needed

  // 7. Generate clip/mask if needed
  
  // 8. Set blend mode
  
  // 9. Paint to surface
  
  // 10. Pop Matrix
  cairo_restore( cr );
}