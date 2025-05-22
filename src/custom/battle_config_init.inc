// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom battle config initializations
 * Place the definition of custom battle configuration initializations in this file.
 *
 * Do not forget to add a comma at the end of the line, if you want to add another config
 *
 * Format:
 *	 { "name", &battle_config.<variable name>, <default value>, <minimum value>, <maximum value> },
 **/

/**
* Extended Vending system [Lilith]
**/
	{ "extended_vending",					&battle_config.extended_vending,				1,		0,		1,				},
	{ "show_broadcast_info",				&battle_config.show_broadcast_info,				1,		0,		1,				},
	{ "show_item_vending",					&battle_config.show_item_vending,				1,		0,		1,				},
	{ "ex_vending_info",					&battle_config.ex_vending_info,					1,		0,		1,				},
	{ "ex_vending_report",					&battle_config.ex_vending_report,				1,		0,		1,				}, // [Easycore]
	{ "ex_buying_bound",					&battle_config.ex_buying_bound,					1,		0,		1,				}, // [Easycore]
	{ "item_zeny",							&battle_config.item_zeny,						0,		0,		INT32_MAX,		},
	{ "item_cash",							&battle_config.item_cash,						0,		0,		INT32_MAX,		},


	//Extended Battleground
	{ "bg_rotation_mode",                   &battle_config.bg_rotation_mode,                0,      0,      1               },
	{ "bg_idle_announce",                   &battle_config.bg_idle_announce,                0,      0,      INT_MAX,        },
	{ "bg_idle_autokick",                   &battle_config.bg_idle_autokick,                0,      0,      INT_MAX,        },
	{ "bg_reward_rates",                    &battle_config.bg_reward_rates,                 100,    0,      INT_MAX,        },
	{ "bg_reward_rates_vip",                &battle_config.bg_reward_rates_vip,             0,      0,      INT_MAX,        },
	{ "bg_reportafk_leaderonly",            &battle_config.bg_reportafk_leaderonly,         1,      0,      1,              },
	{ "bg_queue_onlytowns",                 &battle_config.bg_queue_onlytowns,              1,      0,      1,              },
	{ "bg_reserved_char_id",                &battle_config.bg_reserved_char_id,             999996, 0,      INT_MAX,        },
	{ "woe_reserved_char_id",				&battle_config.woe_reserved_char_id,            999997, 0,      INT_MAX,        },
	{ "bg_can_trade",				        &battle_config.bg_can_trade,                    1,      0,      1,              },
	{ "bg_double_login",				    &battle_config.bg_double_login,                 1,      0,      1,              },
	{ "bg_extended_check_equip",			&battle_config.bg_extended_check_equip,         1,      0,      1,              },
	{ "bg_queue_confirmation",			    &battle_config.bg_queue_confirmation,           1,      0,      1,              },
	{ "bg_queue_interface",					&battle_config.bg_queue_interface,       	    1,      0,      1,              },
	{ "bg_remove_buffs",			        &battle_config.bg_remove_buffs,                 0,      0,      63,             },
	{ "bg_buffs_on_leave",			        &battle_config.bg_buffs_on_leave,               0,      0,      1,             },
	{ "bg_balance_teams",			        &battle_config.bg_balance_teams,                0,      0,      1,             },
	{ "bg_monsters_skillimmune",			&battle_config.bg_monsters_skillimmune,         0,      0,      1,             },
