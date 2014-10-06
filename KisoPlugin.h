#include "uv.h"
#include "KisoApp.h"

class KisoPlugin {
public: 
	KisoPlugin( KisoApp* app ) : m_app(app) {};
	virtual ~KisoPlugin() {};
protected:
	KisoApp* m_app;
};