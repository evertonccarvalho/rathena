// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom battle config structure
 * Place the definition of custom battle configuration structure members in this file.
 *
 * Make sure that the name you want is not already taken by looking into battle.hpp
 * Do not forget to add initilization logic to battle_config_init.inc
 *
 * Format:
 *	 <datatype> name;
 **/

/**
* Extended Vending system [Lilith]
**/
int extended_vending;
int show_broadcast_info;
int show_item_vending;
int ex_vending_info;
int ex_vending_report;
int ex_buying_bound;
int item_zeny;
int item_cash;

int32 bg_rotation_mode;
int32 bg_idle_announce;
int32 bg_idle_autokick;
int32 bg_reportafk_leaderonly;
int32 bg_reward_rates;
int32 bg_reward_rates_vip;
int32 bg_queue_onlytowns;
int32 bg_reserved_char_id;
int32 woe_reserved_char_id;
int32 bg_can_trade;
int32 bg_double_login;
int32 bg_extended_check_equip;
int32 bg_queue_confirmation;
int32 bg_queue_interface;
int32 bg_remove_buffs;
int32 bg_buffs_on_leave;
int32 bg_balance_teams;
int32 bg_monsters_skillimmune;
