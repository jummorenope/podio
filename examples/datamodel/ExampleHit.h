#ifndef ExampleHit_H
#define ExampleHit_H
#include "ExampleHitData.h"

#include <vector>
#include "albers/ObjectID.h"

// measured energy deposit
// author: B. Hegner

//forward declarations
class ExampleHitCollection;
class ExampleHitCollectionIterator;
class ExampleHitObj;

#include "ExampleHitObj.h"

class ExampleHit {

  friend ExampleHitCollection;
  friend ExampleHitCollectionIterator;

public:

  /// default constructor
  ExampleHit();
  /// copy constructor
  ExampleHit(const ExampleHit& other);
  /// copy-assignment operator
  ExampleHit& operator=(const ExampleHit& other);
  /// constructor from existing ExampleHitObj
  ExampleHit(ExampleHitObj* obj);
  /// destructor
  ~ExampleHit();

  const double& x() const;
  const double& y() const;
  const double& z() const;
  const double& energy() const;

  void x(double value);
  void y(double value);
  void z(double value);
  void energy(double value);


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ExampleHitObj instance
  void unlink(){m_obj = nullptr;};

  bool operator==(const ExampleHit& other) const {
       return (m_obj==other.m_obj);
  }

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const ExampleHit& p1,
//       const ExampleHit& p2 );

  const albers::ObjectID getObjectID() const;

private:
  ExampleHitObj* m_obj;

};

#endif
