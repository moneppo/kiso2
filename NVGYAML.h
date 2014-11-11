#include "yaml-cpp/yaml.h"
#include "nanovg.h"

#define SAFEFIND(r, k, d) (r[k]!=NULL?r[k].as<typeof d>():d)
//#define SAFEFIND(r,k,d) d

namespace YAML {
	
	template<>
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
			rhs.r = rhs.g = rhs.b = rhs.a = 0;
			if (node.IsNull()) {
				return true;
			}
			
			if(node.IsSequence()) {
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
			
			if (node.IsMap()) {
				rhs.r = SAFEFIND(node, "r", 0);
				rhs.g = SAFEFIND(node, "g", 0);
				rhs.b = SAFEFIND(node, "b", 0);
				rhs.a = SAFEFIND(node, "a", 0);
				return true;
			}
			
			return false;
		}
	};
}