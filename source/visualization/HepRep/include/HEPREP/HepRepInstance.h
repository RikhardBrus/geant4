// -*- C++ -*-
// AID-GENERATED
// =========================================================================
// This class was generated by AID - Abstract Interface Definition          
// DO NOT MODIFY, but use the org.freehep.aid.Aid utility to regenerate it. 
// =========================================================================
#ifndef HEPREP_HEPREPINSTANCE_H
#define HEPREP_HEPREPINSTANCE_H 1

// Copyright 2000-2002, FreeHEP.

#include <vector>

#include "HEPREP/HepRepAttribute.h"

namespace HEPREP {

class HepRep;
class HepRepInstanceTree;
class HepRepPoint;
class HepRepSelectFilter;
class HepRepType;

/**
 * HepRepInstance interface.
 *
 * @author Mark Donszelmann
 */
class HepRepInstance : virtual public HepRepAttribute {

public: 
    /// Destructor.
    virtual ~HepRepInstance() { /* nop */; }

    /**
     * Overlays the instance on the current instance.
     *
     * Attributes of the instance override or are added to the current instance.
     * Sub-instances of the instance are added only if the current instance has no sub-instances.
     * Points of the instance are added only if the current instance has no points.
     */
    virtual void overlay(HepRepInstance * instance) = 0;

    /**
     * Adds an sub-instance to this instance.
     *
     * @param instance sub-instance.
     * @return false only if written immediately to a stream.
     */
    virtual bool addInstance(HepRepInstance * instance) = 0;

    /**
     * Removes a sub-instance from this instance.
     *
     * @param instance sub-instance.
     */
    virtual void removeInstance(HepRepInstance * instance) = 0;

    /**
     * Returns a collection of all sub-instances this instance keeps.
     *
     * @return collection of HepRepInstances.
     */
    virtual std::vector<HepRepInstance *>  * getInstances() = 0;

    /**
     * Returns the associated type for this instance.
     *
     * @return associated HepRepType.
     */
    virtual HepRepType * getType() = 0;

    /**
     * Adds a point to this instance.
     *
     * @param point to be added.
     * @return false only if written immediately to a stream.
     */
    virtual bool addPoint(HepRepPoint * point) = 0;

    /**
     * Returns a collection of all points this instance keeps.
     *
     * @return collection of HepRepPoints.
     */
    virtual std::vector<HepRepPoint *>  * getPoints() = 0;

    /**
     * Returns a deep copy of this instance.
     *
     * @param heprep needed to find the associated type.
     * @param parent to which the copy is added.
     * @param filter run on all instances before copying.
     * @return copy of this instance.
     */
    virtual HepRepInstance * copy(HepRep * heprep, HepRepInstance * parent, HepRepSelectFilter * filter = NULL) = 0;

    /**
     * Returns a deep copy of this instance.
     *
     * @param heprep needed to find the associated type.
     * @param parent to which the copy is added.
     * @param filter run on all instances before copying.
     * @return copy of this instance.
     */
    virtual HepRepInstance * copy(HepRep * heprep, HepRepInstanceTree * parent, HepRepSelectFilter * filter = NULL) = 0;
}; // class
} // namespace HEPREP
#endif /* ifndef HEPREP_HEPREPINSTANCE_H */
