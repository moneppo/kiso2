package kiso.YAML;

import java.io.*;
import java.util.*;
import kiso.YAML.Map;
import java.lang.Integer;

class Sequence {
  
  private Sequence() 
  {
    initialize();
  }
  
  static { 
    System.loadLibrary("Sequence"); 
  }
  
  native protected synchronized void initialize();
  
  native public synchronized String getScalar(int index);
  native public synchronized Sequence getSequence(int index);
  native public synchronized Map getMap(int index);
  native public synchronized String type(int index);
  
  native public synchronized int length();
  native public synchronized void remove(int index);

  native public synchronized void setScalar(int index, String s);
  native public synchronized void setSequence(int index, Sequence s);
  native public synchronized void setMap(int index, Map s);
  
  protected class SequenceIterator implements Iterator
  {
    protected int current;

    SequenceIterator() {
      current = 0;
    }

    public boolean hasNext() {
      return current < length();
    }

    public Object next() {
      current++;
      return new Integer(current);
    }

    public void remove() {
      throw new UnsupportedOperationException();
    }
  }

  public Iterator iterator() {
    return new SequenceIterator();
  }
}