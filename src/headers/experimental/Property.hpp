#ifdef EXPERIMENTAL

  #ifndef PROPERTY_HPP
  #define PROPERTY_HPP

  #include "Float.hpp"
  #include <map>
  #include <string>
  #include <exception>

  using namespace std;

  enum class PropertyType {Integer, Float, Bool};

/*  class PropertyValue {
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

  };*/

  class PropertyHolder {
  protected:
    map <string, PropertyType> properties;
  public:
    virtual void set (string name, int value);

    virtual void set (string name, FLOAT value);
    virtual void set (string name, bool value);

    virtual int getInt(string pName);
    virtual FLOAT getFloat(string pName);
    virtual bool  getBool(string pName);


  };




  #endif
#endif
