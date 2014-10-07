#ifndef KisoRenderer_Header
#define KisoRenderer_Header

#include "yaml-cpp/yaml.h"
#include "vector.h"
#include "cairo.h"
#include "KisoApp.h"

namespace YAML {
	static Node operator|=(Node a, const Node &b) {
  	if (b.IsMap()) {
    	for (auto n0 : b) {
      	a[n0.first.Scalar()] |= n0.second;
    	}
  	} else {
    	a = b;
  	}
  	return a;
	}
}


class KisoRenderer {
public:
  KisoRenderer();
  YAML::Node& presentation();
	void queueRender( cairo_t* cr, KisoApp* app );
  
private:
	YAML::Node mergeNodes( YAML::Node base, YAML::Node overlay1, YAML::Node overlay2 );
	
	void drawBorder( cairo_t* cr, YAML::Node& style, YAML::Node& layout );             
	void drawBackground( cairo_t* cr,  YAML::Node& style, YAML::Node& layout );
	
	YAML::Node computeLayout( std::string name, YAML::Node node, YAML::Node& parent );
	YAML::Node computeStyle( std::string name, YAML::Node node, YAML::Node& parent );
	
  void drawNode( cairo_t* cr,  YAML::Node& node, YAML::Node& style, YAML::Node& layout );
	void draw2DChildren( cairo_t* cr,  YAML::Node& node );
	void drawGridChildren( cairo_t* cr,  YAML::Node& node, YAML::Node& layout ) ;
  void drawFillChildren( cairo_t* cr,  YAML::Node& node, YAML::Node& layout ) ;
	YAML::Node m_presentation;
  cairo_matrix_t buildTransform(YAML::Node& element );
};

#endif