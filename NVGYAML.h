#include "yaml-cpp/yaml.h"
#include "nanovg.h"

struct convert<NVGcolor> {
	static Node encode(const NVGcolor& rhs) {
		Node node;
		node.push_back(rhs.r);
		node.push_back(rhs.g);
		node.push_back(rhs.b);
		node.push_back(rhs.a);
		return node;
	}

	static bool decode(const Node& node, NVGcolor& rhs) {
		if(!node.IsSequence()) {
			return false;
		}
		rhs.r = rhs.g = rhs.b = rhs.a = 0;

		int size = node.size();
		if (size >= 1) {
			rhs.r = node[0].as<float>();
		}

		if (size >= 2) {
			rhs.g = node[1].as<float>();
		}

		if (size >= 3) {
			rhs.b = node[2].as<float>();
		}
		
		if (size >= 3) {
			rhs.a = node[3].as<float>();
		}

		return true;
	}
};