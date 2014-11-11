#include "KisoRenderer.h"
#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg_gl.h"

using namespace std;

KisoRenderer::KisoRenderer(vec2i size, float aspectRatio, bool debug) :
	m_size(size), m_aspectRatio(aspectRatio)
{
	int flags = NVG_ANTIALIAS | NVG_STENCIL_STROKES;
	if (debug) {
		flags |= NVG_DEBUG;
	}
	m_vg = nvgCreateGL2(flags);

	if (m_vg == NULL) {
		cerr << "Could not init nanovg." << endl;
		throw -1;
	}
}

KisoRenderer::~KisoRenderer() {
	nvgDeleteGL2(m_vg);
}

mat2x3f KisoRenderer::buildTransform( YAML::Node& layout )
{
	return mat2x3f();
}

void KisoRenderer::render( KisoApp* app )
{
  YAML::Node presentation = YAML::Clone(*(app->presentation()));
	//YAML::Node style = presentation["style"];
	//YAML::Node layout = presentation["layout"];
	//drawNode( *(app->structure()), style, layout );
}

YAML::Node KisoRenderer::mergeNodes(YAML::Node base, YAML::Node overlay1, YAML::Node overlay2)
{
	YAML::Node output = YAML::Clone(base);
  output |= overlay1;
	output |= overlay2;
	
	return output;
}

void KisoRenderer::drawBorder( YAML::Node& style, YAML::Node& layout )
{	
	float radius = SAFEFIND(style, "border-radius", 0.0f);
	float width = SAFEFIND(style, "border-width", 0.0f);
	NVGcolor color = SAFEFIND(style, "border-color", nvgRGB(0,0,0));
	vec3d position = SAFEFIND(style, "position", vec3d(0,0,0));
	vec2d size = SAFEFIND(layout, "size", vec2d(0,0));
  
	nvgStrokeColor(m_vg, color);
  nvgStrokeWidth(m_vg, width);
	nvgBeginPath(m_vg);
	nvgRoundedRect(m_vg, position.x, position.y, size.x, size.y, radius);
 	nvgStroke(m_vg);
}

int KisoRenderer::locateImage(string filename) {
	int img;
	NVGImageMap::iterator imgIt = m_images.find(filename);
	if (imgIt == m_images.end()) {
		img = nvgCreateImage(m_vg, filename.c_str(), 0);
		m_images[filename] = img;
	} else {
		img = imgIt->second;
	}
	return img;
}

void KisoRenderer::drawBackground( YAML::Node& style, YAML::Node& layout )
{
	NVGcolor color = SAFEFIND(style, "background-color", nvgRGB(0,0,0));
  string filename = SAFEFIND(style, "background-image", string());
	vec3d position = SAFEFIND(style,  "position", vec3d(0,0,0));
	vec2d size = SAFEFIND(layout, "size", vec2d(0,0));
	
	// TODO: Implement offset & angle, and add ability to set size of image
	vec2d offset    = vec2d();
	float angle = 0;
	float alpha = 1.0;
  
  if (filename != "") {
		int img = locateImage(filename);
		NVGpaint paint = nvgImagePattern(
			m_vg, offset.x, offset.y, 
			size.x, size.y, angle, img, alpha);
		nvgFillPaint(m_vg, paint);
  } else {
   	nvgFillColor(m_vg, color);
  }
	
	// TODO: Rounded amount
	nvgRoundedRect(m_vg, position.x, position.y, size.x, size.y, 0);
	nvgFill(m_vg);
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

void KisoRenderer::drawGridChildren( YAML::Node& node, YAML::Node& layout ) 
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
      drawNode( child, style, childLayout );
    }
  }
}

void KisoRenderer::drawFillChildren( YAML::Node& node, YAML::Node& layout ) 
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
      drawNode( child, style, childLayout );
    }
  }
}

void KisoRenderer::draw2DChildren( YAML::Node& node ) 
{
  for ( YAML::const_iterator it = node.begin(); it!=node.end(); ++it )
  {
    string name = it->first.as<std::string>();
    if ( name != "style" && name != "layout" )
    {
      YAML::Node childLayout = computeLayout( name, *it, node );
      YAML::Node style = computeStyle( name, *it, node );
			YAML::Node child = *it;
      drawNode( child, style, childLayout );
    }
  }
}


void KisoRenderer::drawNode( YAML::Node& node, YAML::Node& style, YAML::Node& layout ) 
{

  // 0. Push matrix
  nvgSave(m_vg);
  
  // 1. Apply transform
	mat2x3f mat = buildTransform(layout);
	nvgTransform(m_vg, mat.a, mat.b, mat.c, mat.d, mat.e, mat.f);

  // 2. Draw shadow
  //drawShadow( style, layout );
  
  // 3. Draw background
  drawBackground ( style, layout );
  
  // 4. Draw border
  drawBorder ( style, layout ); 
    
  //5. Draw Children
  string type = layout["type"].as<string>();
  if ( type == "2D" )
  {
    draw2DChildren( node );
  }
  else if ( type == "fill" )
  {
    drawFillChildren( node, layout );
  }
  else if ( type == "grid" )
  {
    drawGridChildren( node, layout );
  }
  
  // 6. Draw text if needed

  // 7. Generate clip/mask if needed
  
  // 8. Set blend mode
  
  // 9. Paint to surface
  
  // 10. Pop Matrix
  nvgRestore(m_vg);
}