package kiso;

import kiso.YAML.*;

class App {
  public App() {
    initialize();
  }
  
  public native synchronized Map getStructure();
  public native synchronized Map getPresentation();
  
  protected native synchronized initialize();
}