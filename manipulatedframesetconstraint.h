#ifndef MANIPULATEDFRAMESETCONSTRAINT_H
#define MANIPULATEDFRAMESETCONSTRAINT_H
#include "QGLViewer/constraint.h"
#include "object.h"

class ManipulatedFrameSetConstraint : public qglviewer::Constraint {
public:
  void clearSet();
  void addObjectToSet(Object *o);

  virtual void constrainTranslation(qglviewer::Vec &translation,
                                    qglviewer::Frame *const frame);
  virtual void constrainRotation(qglviewer::Quaternion &rotation,
                                 qglviewer::Frame *const frame);

private:
  QList<Object *> objects_;
};

//class manipulatedFrameSetConstraint : public qglviewer
//{
//public:
//    manipulatedFrameSetConstraint();
//};

#endif // MANIPULATEDFRAMESETCONSTRAINT_H
