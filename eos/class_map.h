// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_CLASS_MAP_H
#define EOS_CLASS_MAP_H

#include <map>
#include <utility>

#include <eos/acl.h>
#include <eos/iterator.h>
#include <eos/policy_map.h>

/**
 * Class map manipulation.
 *
 * This module provides access to the management of class maps.
 * Classification or "class" maps, provide a way for the network
 * operator to classify packets arriving on an interface. Together
 * with the policy_map_mgr in policy_map.h, classified traffic can drive
 * policy features, such as PBR.
 */

namespace eos {

/**
 * A special class map name which means "match all MPLS traffic"
 *
 * Use as follows when defining a class_map_key_t:
 *
 * @code{.cpp}
 *   eos::class_map_key_t key(eos::CLASS_MAP_MPLS_ANY, eos::POLICY_FEATURE_PBR);
 *   eos::class_map_t cm(key);
 * @endcode
 *
 * Only one such rule can be set on any one policy map.
 */
static std::string const CLASS_MAP_MPLS_ANY("__mpls_permit_any__");

typedef policy_map_key_t class_map_key_t;

/**
 * A class map match rule uses an ACL to match classified traffic.
 *
 * Values of this type are returned from the class_map_rule_iter,
 * to program class maps, either supply one of these or the acl_key_t
 * directly to class_map_mgr's class_map_rule_set().
 */
class EOS_SDK_PUBLIC class_map_rule_t {
 public:
   class_map_rule_t();
   explicit class_map_rule_t(acl_key_t const & acl_key);

   /// The ACL name and type to use as a class map match rule.
   acl_key_t const & acl_key() const;

   bool operator==(class_map_rule_t const &) const;
   bool operator!=(class_map_rule_t const &) const;

 private:
   acl_key_t acl_key_;
};

/**
 * A class map. Classifies traffic to apply policy features to.
 *
 * A class map can match IP or MPLS traffic. To match IP traffic,
 * specify a class map matching one or more IPv4 ACLs (for PBR).
 */
class EOS_SDK_PUBLIC class_map_t {
 public:
   class_map_t();
   explicit class_map_t(class_map_key_t const & key);

   /// Returns the class map key
   class_map_key_t key() const;
   /// Sets the class map key
   void key_is(class_map_key_t const & key);

   /// Returns the map of sequence number to class map rule for this class map
   std::map<uint32_t, class_map_rule_t> const & rules() const;

   /// Sets the sequence of class map rules
   void rules_is(std::map<uint32_t, class_map_rule_t> const &);

   /// Sets a class map rule at a partcular sequence number
   void rule_set(uint32_t, class_map_rule_t const &);

   /// Removes the provided sequence rule entry from the class map
   void rule_del(uint32_t);

   /// Sets the config persistence for this class map (defaults to false).
   void persistent_is(bool);

   /**
    * The persistence state for this class map.
    *
    * When true, the class map will be stored in the running
    * and startup configuration.
    */
   bool persistent() const;

   bool operator==(class_map_t const &) const;
   bool operator!=(class_map_t const &) const;

 private:
   class_map_key_t key_;
   std::map<uint32_t, class_map_rule_t> rules_;
   bool persistent_;
};

class class_map_iter_impl;

/// An iterator providing forwards only iteration over collections of class maps
class EOS_SDK_PUBLIC class_map_iter_t : public iter_base<class_map_key_t,
                                                         class_map_iter_impl> {
 private:
   friend class class_map_iter_impl;
   explicit class_map_iter_t(class_map_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * EOS class map manager.
 *
 * This manager provides access to EOS traffic classifers, or "class
 * maps". Class maps are referred to by policy maps (policy_map.h) to classify
 * traffic that should be subject to the policy's actions.
 */
class EOS_SDK_PUBLIC class_map_mgr {
 public:
   virtual ~class_map_mgr();

   /**
    * Resync mediates class map configuration into a known good state.
    *
    * To start a resync, call resync_init() and then use the functions
    * in the module to manipulate class maps like normal, setting them
    * with class_map_is(). After all entries have been set, call
    * resync_complete(), which will delete existing class_maps that
    * were not added or modified during resync.
    *
    * During resync, this manager will act like it is referencing a
    * temporary table that starts off empty. Thus, methods like exist,
    * del, and getters will act only on that temporary table,
    * regardless of the real values in Sysdb. The one exception is
    * iteration; they will traverse the table stored in Sysdb,
    * regardless of whether or not the manager is in resync mode.
    */
   virtual void resync_init() = 0;
   /// Completes any underway resync operation.
   virtual void resync_complete() = 0;

   /// Returns true if and only if the provided key exists in the system config
   virtual bool exists(class_map_key_t const & key) const = 0;

   /**
    * Returns the class map for the provided class map key.
    * If there is no class map for the key, returns a default class_map_t
    */
   virtual class_map_t class_map(class_map_key_t const & key) const = 0;

   /// Sets a class map and commits its configuration
   virtual void class_map_is(class_map_t const & class_map) = 0;

   /// Provides iteration over the configured class maps for a feature
   virtual class_map_iter_t class_map_iter(policy_feature_t) const = 0;

   /// Deletes the class map specified
   virtual void class_map_del(class_map_key_t const & key) = 0;

 protected:
   class_map_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(class_map_mgr);
};

} // end namespace eos

#include <eos/inline/class_map.h>

#endif // EOS_CLASS_MAP_H
