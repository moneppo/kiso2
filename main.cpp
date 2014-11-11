#include "KisoGLFWViewer.h"
#include "KisoApp.h"
#include "KisoRenderer.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
	KisoApp theApp("foo", "bar");
	KisoGLFWViewer theViewer(true);
	//theApp.startVM();
	return theViewer.run(&theApp);
}