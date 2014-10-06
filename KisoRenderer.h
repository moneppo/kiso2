#include "yaml-cpp/yaml.h"
#include "vector.h"
#include "cairo.h"

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
  void setPresentation( YAML::Node& presentation );
  YAML::Node& presentation();
  
private:
	YAML::Node mergeNodes( YAML::Node base, YAML::Node overlay1, YAML::Node overlay2 );
	
	void drawBorder( YAML::Node& style, YAML::Node& layout );             
	void drawBackground( YAML::Node& style, YAML::Node& layout );
	
	YAML::Node computeLayout( std::string name, YAML::Node node, YAML::Node& parent );
	YAML::Node computeStyle( std::string name, YAML::Node node, YAML::Node& parent );

	
  void drawNode( YAML::Node& node, YAML::Node& style, YAML::Node& layout );
	void draw2DChildren( YAML::Node& node );
	void drawGridChildren( YAML::Node& node, YAML::Node& layout ) ;
  void drawFillChildren( YAML::Node& node, YAML::Node& layout ) ;
	cairo_t* m_cr;
	YAML::Node m_presentation;
  cairo_matrix_t buildTransform(YAML::Node& element );
};