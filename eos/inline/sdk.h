// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_SDK_H
#define EOS_INLINE_SDK_H

namespace eos {

inline void sdk::main_loop(const char * agent_name, int argc, char ** argv) {
   get_agent_mgr()->main_loop(agent_name, argc, argv);
}

inline acl_mgr * sdk::get_acl_mgr() {
   if (!acl_mgr_) {
      init_acl_mgr();
   }
   return acl_mgr_;
}

inline agent_mgr * sdk::get_agent_mgr() {
   if (!agent_mgr_) {
      init_agent_mgr();
   }
   return agent_mgr_;
}

inline decap_group_mgr * sdk::get_decap_group_mgr() {
   if (!decap_group_mgr_) {
      init_decap_group_mgr();
   }
   return decap_group_mgr_;
}

inline directflow_mgr * sdk::get_directflow_mgr() {
   if (!directflow_mgr_) {
      init_directflow_mgr();
   }
   return directflow_mgr_;
}

inline eth_intf_mgr * sdk::get_eth_intf_mgr() {
   if (!eth_intf_mgr_) {
      init_eth_intf_mgr();
   }
   return eth_intf_mgr_;
}

inline eth_phy_intf_mgr * sdk::get_eth_phy_intf_mgr() {
   if (!eth_phy_intf_mgr_) {
      init_eth_phy_intf_mgr();
   }
   return eth_phy_intf_mgr_;
}

inline fib_mgr * sdk::get_fib_mgr() {
   if (!fib_mgr_) {
      init_fib_mgr();
   }
   return fib_mgr_;
}

inline intf_mgr * sdk::get_intf_mgr() {
   if (!intf_mgr_) {
      init_intf_mgr();
   }
   return intf_mgr_;
}

inline ip_route_mgr * sdk::get_ip_route_mgr() {
   if (!ip_route_mgr_) {
      init_ip_route_mgr();
   }
   return ip_route_mgr_;
}

inline mac_table_mgr * sdk::get_mac_table_mgr() {
   if (!mac_table_mgr_) {
      init_mac_table_mgr();
   }
   return mac_table_mgr_;
}

inline mlag_mgr * sdk::get_mlag_mgr() {
   if (!mlag_mgr_) {
      init_mlag_mgr();
   }
   return mlag_mgr_;
}

inline mount_mgr * sdk::get_mount_mgr() {
   if (!mount_mgr_) {
      init_mount_mgr();
   }
   return mount_mgr_;
}

inline mpls_route_mgr * sdk::get_mpls_route_mgr() {
   if (!mpls_route_mgr_) {
      init_mpls_route_mgr();
   }
   return mpls_route_mgr_;
}

inline neighbor_table_mgr * sdk::get_neighbor_table_mgr() {
   if (!neighbor_table_mgr_) {
      init_neighbor_table_mgr();
   }
   return neighbor_table_mgr_;
}

inline nexthop_group_mgr * sdk::get_nexthop_group_mgr() {
   if (!nexthop_group_mgr_) {
      init_nexthop_group_mgr();
   }
   return nexthop_group_mgr_;
}

inline policy_map_mgr * sdk::get_policy_map_mgr() {
   if (!policy_map_mgr_) {
      init_policy_map_mgr();
   }
   return policy_map_mgr_;
}

inline system_mgr * sdk::get_system_mgr() {
   if (!system_mgr_) {
      init_system_mgr();
   }
   return system_mgr_;
}

}

#endif // EOS_INLINE_SDK_H