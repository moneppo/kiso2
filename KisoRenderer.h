#ifndef KisoRenderer_Header
#define KisoRenderer_Header

#include "yaml-cpp/yaml.h"
#include "vector.h"
#ifdef __APPLE__
	#include <OpenGL/gl.h>
#endif

#include "nanovg.h"

#include "KisoApp.h"
#include "NVGYAML.h"

#include <iostream>
#include <string>
#include <unordered_map>

typedef std::unordered_map<std::string, int> NVGImageMap;

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
  KisoRenderer(vec2i size, float aspectRatio, bool debug = false);
	virtual ~KisoRenderer();
  YAML::Node& presentation();
	void render( KisoApp* app );
  
private:
	YAML::Node mergeNodes( YAML::Node base, YAML::Node overlay1, YAML::Node overlay2 );
	
	int locateImage(std::string filename);
	
	void drawBorder( YAML::Node& style, YAML::Node& layout );             
	void drawBackground( YAML::Node& style, YAML::Node& layout );
	
	YAML::Node computeLayout( std::string name, YAML::Node node, YAML::Node& parent );
	YAML::Node computeStyle( std::string name, YAML::Node node, YAML::Node& parent );
	
  void drawNode( YAML::Node& node, YAML::Node& style, YAML::Node& layout );
	void draw2DChildren( YAML::Node& node );
	void drawGridChildren( YAML::Node& node, YAML::Node& layout ) ;
  void drawFillChildren( YAML::Node& node, YAML::Node& layout ) ;
	YAML::Node m_presentation;
  mat2x3f buildTransform(YAML::Node& element );
	
	NVGcontext* m_vg;
	vec2i m_size;
	vec2d m_aspectRatio;
	NVGImageMap m_images;
};

#endif