// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Script Commands
 * Place the definition of custom script commands in this file.
 * Format:
 *	BUILDIN_DEF(command_name,"parameters"),
 **/

//BUILDIN_DEF(example,""),

//Extended Battleground [Easycore]
BUILDIN_DEF(bg_queue_join,"si?"),
BUILDIN_DEF(bg_queue_leave_all,""),
BUILDIN_DEF(getcharqueue,"?"),
BUILDIN_DEF(bg_queue_show,"?"),
BUILDIN_DEF(viewpointmap2, "siiiii"),
BUILDIN_DEF(bg_team_reveal, "ii"),
BUILDIN_DEF(bg_afk_warning, "ii"),
BUILDIN_DEF(bg_getitem, "iiii"),
BUILDIN_DEF(bg_reward, "iiiiisiiii"),
BUILDIN_DEF(bg_flagemblem, "i"),
BUILDIN_DEF(bg_monster_reveal, "iii"),
BUILDIN_DEF(bg_queue_info, "ii"),
BUILDIN_DEF(bg_set_data, "iiii"),
BUILDIN_DEF(bg_queue_finish, "i"),
BUILDIN_DEF(bg_queue_transfer_all,"ss"),
BUILDIN_DEF(donpceventall, "s"),
BUILDIN_DEF(bg_rankpoints,"iii?"),
BUILDIN_DEF(bg_rankpoints_team,"iiii"),
BUILDIN_DEF(bg_rankpoints_area,"isiiiiiii"),
BUILDIN_DEF(battle_rank_reset,"i"),
BUILDIN_DEF(bg_set_cemetery,"isii"),
BUILDIN_DEF(bg_announce, "s?????"),
BUILDIN_DEF(bg_soundeffect, "si"),
BUILDIN_DEF(bg_specialeffect, "ii"),
BUILDIN_DEF(bg_emotion, "ii"),
BUILDIN_DEF(bg_team_leave, "i"),
BUILDIN_DEF(bg_clear_buffs, "ii"),
BUILDIN_DEF(bg_clear_buffs_area, "iisiiii"),
BUILDIN_DEF(bg_warp_cemetery, "i"),
BUILDIN_DEF(bg_sc_end, "ii"),
BUILDIN_DEF(bg_sc_start,"iiii???"),
BUILDIN_DEF2(bg_sc_start,"bg_sc_start2","iiiii??"),
BUILDIN_DEF2(bg_sc_start,"bg_sc_start4","iiiiiii??"),
BUILDIN_DEF(bg_percentheal, "iii"),
BUILDIN_DEF(getcharrank,"i?"),
