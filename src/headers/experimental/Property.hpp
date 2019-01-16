#ifdef EXPERIMENTAL

  #ifndef PROPERTY_HPP
  #define PROPERTY_HPP

  #include "Float.hpp"
  #include <map>
  #include <string>
  #include <exception>

  using namespace std;

  enum class PropertyType {Integer, Float, Bool};

  class PropertyValue {
  private:
    void * value = nullptr;
    PropertyType pType;

  public:
    PropertyValue(int newValue);
    PropertyValue(FLOAT value);
    PropertyValue(bool value);
    FLOAT getFloat();
    int getInt();
    bool getProperty();
    ~PropertyValue();

  };

  class PropertyHolder {
  private:
    map <string, PropertyType> properties;
  public:
    virtual void set (string name, int value);

    virtual void set (string name, FLOAT value);
    virtual void set (string name, bool value);


    int getInt(string pName);
    int getFloat(string pName);
    int getBool(string pName);


  };



  #endif
#endif
