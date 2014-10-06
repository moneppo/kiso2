package kiso.YAML;

import java.io.*;
import java.util.*;
import kiso.YAML.Sequence;

class Map {
  
  private Map() 
  {
    initialize();
  }
  
  static { 
    System.loadLibrary("Map"); 
  }
  
  native protected synchronized void initialize();
  
  native public synchronized String getScalar(String key);
  native public synchronized Sequence getSequence(String key);
  native public synchronized Map getMap(String key);
  native public synchronized String type(String key);
  
  native public synchronized int size();
  native public synchronized void remove(String key);

  native public synchronized void setScalar(String key, String s);
  native public synchronized void setSequence(String key, Sequence s);
  native public synchronized void setMap(String key, Map s);
  
  native public synchronized String firstKey();
  native public synchronized String nextKey(String key);
  
  protected class MapIterator implements Iterator
  {
    protected String current;

    MapIterator() {
      current = firstKey();
    }

    public boolean hasNext() {
      return current != null;
    }

    public Object next() {
      String s = current;
      current = nextKey( current );
      return s;
    }

    public void remove() {
      throw new UnsupportedOperationException();
    }
  }

  public Iterator iterator() {
    return new MapIterator();
  }
}