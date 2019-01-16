#ifdef EXPERIMENTAL

  #ifndef PROPERTY_HPP
  #define PROPERTY_HPP

  enum class PropertyType {Integer, Float, Bool};

  class PropertyValue {
  private:
    void * value = nullptr;
    PropertyType pType;

  public:
    PropertyValue::PropertyValue(int newValue);
    PropertyValue::PropertyValue(FLOAT value);
    PropertyValue::PropertyValue(bool value);
    FLOAT getFloat();
    int getInt();
    bool getProperty();
    ~PropertyValue()

  };

  class PropertyHolder {
  private:
    map <string, PropertyType> properties;
  public:
    virtual void set (string name, int value);

    virtual void set (string name, FLOAT value);
    virtual void set (string name, bool value);

    <template class = T>
    virtual T get(string pName) =0;


  };

  

  #endif
#endif
