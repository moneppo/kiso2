#include "yaml-cpp/yaml.h"

struct vec4d {
	vec4d(double _x = 0.0, double _y = 0.0, 
				double _z = 0.0, double _w = 0.0) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	union {
		double x;
		double r;
	};
	
	union {
		double y;
		double g;
	};
	
	union {
		double z;
		double b;
	};
	
	union {
		double w;
		double a;	
	};
};

struct vec3d {
	vec3d(double _x = 0.0, double _y = 0.0, double _z = 0.0) {
		x = _x;
		y = _y;
		z = _z;
	}
	union {
		double x;
		double r;
	};
	
	union {
		double y;
		double g;
	};
	
	union {
		double z;
		double b;
	};
};


struct vec2d {
	vec2d(double _x = 0.0, double _y = 0.0) {
		x = _x;
		y = _y;
	}
	double x;
	double y;
};

struct vec2i {
	vec2i(int _x = 0.0, int _y = 0.0) {
		x = _x;
		y = _y;
	}
	int x;
	int y;
};

namespace YAML {

template<>
struct convert<vec4d> {
  static Node encode(const vec4d& rhs) {
    Node node;
    node.push_back(rhs.x);
    node.push_back(rhs.y);
    node.push_back(rhs.z);
		node.push_back(rhs.w);
    return node;
  }

  static bool decode(const Node& node, vec4d& rhs) {
    if(!node.IsSequence()) {
      return false;
    }
		rhs.x = rhs.y = rhs.z = rhs.w = 0;
		
		int size = node.size();
		if (size >= 1) {
			rhs.x = node[0].as<double>();
		}
		
		if (size >= 2) {
			rhs.y = node[1].as<double>();
		}
		
		if (size >= 3) {
			rhs.z = node[2].as<double>();
		}
		
		if (size >= 4) {
			rhs.w = node[3].as<double>();
		}
    return true;
  }
};
	
template<>
struct convert<vec3d> {
	static Node encode(const vec3d& rhs) {
		Node node;
		node.push_back(rhs.x);
		node.push_back(rhs.y);
		node.push_back(rhs.z);
		return node;
	}

	static bool decode(const Node& node, vec3d& rhs) {
		if(!node.IsSequence()) {
			return false;
		}
		rhs.x = rhs.y = rhs.z = 0;

		int size = node.size();
		if (size >= 1) {
			rhs.x = node[0].as<double>();
		}

		if (size >= 2) {
			rhs.y = node[1].as<double>();
		}

		if (size >= 3) {
			rhs.z = node[2].as<double>();
		}

		return true;
	}
};

template<>
struct convert<vec2d> {
	static Node encode(const vec2d& rhs) {
		Node node;
		node.push_back(rhs.x);
		node.push_back(rhs.y);
		return node;
	}

	static bool decode(const Node& node, vec2d& rhs) {
		if(!node.IsSequence()) {
			return false;
		}
		rhs.x = rhs.y = 0;

		int size = node.size();
		if (size >= 1) {
			rhs.x = node[0].as<double>();
		}

		if (size >= 2) {
			rhs.y = node[1].as<double>();
		}

		return true;
	}
};

template<>
struct convert<vec2i> {
	static Node encode(const vec2i& rhs) {
		Node node;
		node.push_back(rhs.x);
		node.push_back(rhs.y);
		return node;
	}

	static bool decode(const Node& node, vec2i& rhs) {
		if(!node.IsSequence()) {
			return false;
		}
		rhs.x = rhs.y = 0;

		int size = node.size();
		if (size >= 1) {
			rhs.x = node[0].as<int>();
		}

		if (size >= 2) {
			rhs.y = node[1].as<int>();
		}

		return true;
	}
};
	
}