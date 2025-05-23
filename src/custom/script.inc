// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Script Commands
 * Place the body of custom script commands in this file.
 * Format:
 *	BUILDIN_FUNC(command_name)
 *	{
 *		<code>;
 *	}
 **/

//BUILDIN_FUNC(example)
//{
//	ShowInfo("buildin_example: It works!\n");
//	script_pushint(st,1);
//	return 0;
//}



BUILDIN_FUNC(bg_queue_join)
{
	int num;
	const char *name;
	TBL_PC *sd;

	name = script_getstr(st,2);
	num = script_getnum(st,3);

	if( !script_nick2sd(4,sd) ){
		script_pushint(st,0); //return 0, according docs
		return SCRIPT_CMD_SUCCESS;
	}

	switch( num ) {
		default:
		case 0: bg_queue_join_solo(name, sd); break;
		case 1: bg_queue_join_party(name, sd); break;
		case 2: bg_queue_join_guild(name, sd); break;
	}
	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_queue_leave_all)
{
	bg_queue_leave_all();
	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_queue_transfer_all)
{
	const char * queue_source = script_getstr(st,2);
	const char * queue_dest = script_getstr(st,3);

	if (!bg_queue_transfer_all(queue_source, queue_dest))
		return SCRIPT_CMD_FAILURE;

	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(getcharqueue)
{
	//int num;
	TBL_PC *sd;

	if( !script_nick2sd(2,sd) ){
		script_pushint(st,-1);
		return SCRIPT_CMD_SUCCESS;
	}

	if (!sd->bg_queue_id) {
		script_pushint(st,-1); //return 0, according docs
		return SCRIPT_CMD_SUCCESS;
	}
	script_pushint(st,sd->bg_queue_id);
	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_queue_show)
{
	//int num;
	TBL_PC *sd;

	if( !script_nick2sd(2,sd) ){
		script_pushint(st,0);
		return SCRIPT_CMD_SUCCESS;
	}

	if (!sd->bg_queue_id) {
		script_pushint(st,0); //return 0, according docs
		return SCRIPT_CMD_SUCCESS;
	}
	clif_bg_queue_apply_notify("test", sd);
	return SCRIPT_CMD_SUCCESS;
}



BUILDIN_FUNC(bg_afk_warning)
{
	int bg_id = script_getnum(st, 2);
	bool flag = script_getnum(st, 3) != 0;
	std::shared_ptr<s_battleground_data> bg = util::umap_find(bg_team_db, bg_id);

	if (!bg)
		return SCRIPT_CMD_SUCCESS;

	for (const auto &member : bg->members)
		member.sd->idletime = last_tick;

	bg->afk_warning = flag;
	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_team_reveal)
{
	int bg_id = script_getnum(st, 2);
	bool reveal = script_getnum(st, 3) != 0;
	std::shared_ptr<s_battleground_data> bg = util::umap_find(bg_team_db, bg_id);

	if (!bg)
		return 0;

	bg->reveal_pos = reveal; // Reveal Position Mode
	return 0;
}

int viewpointmap_sub(struct block_list *bl, va_list ap)
{
	map_session_data *sd;
	int npc_id, type, x, y, id, color;
	npc_id = va_arg(ap, int);
	type = va_arg(ap, int);
	x = va_arg(ap, int);
	y = va_arg(ap, int);
	id = va_arg(ap, int);
	color = va_arg(ap, int);
	sd = (map_session_data *)bl;
	clif_viewpoint(*sd, npc_id, type, x, y, id, color);
	return 0;
}

BUILDIN_FUNC(viewpointmap2)
{
	int type, x, y, id, color, m;
	const char *map_name;

	map_name = script_getstr(st, 2);
	if ((m = map_mapname2mapid(map_name)) < 0)
		return SCRIPT_CMD_FAILURE; // Invalid Map

	type = script_getnum(st, 3);
	x = script_getnum(st, 4);
	y = script_getnum(st, 5);
	id = script_getnum(st, 6);
	color = script_getnum(st, 7);

	map_foreachinmap(viewpointmap_sub, m, BL_PC, st->oid, type, x, y, id, color);
	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_monster_reveal)
{
	struct mob_data *md;
	struct block_list *mbl;
	int id = script_getnum(st, 2),
		flag = script_getnum(st, 3),
		color = script_getnum(st, 4);

	if (id == 0 || (mbl = map_id2bl(id)) == NULL || mbl->type != BL_MOB)
		return 0;
	md = (TBL_MOB *)mbl;
	map_foreachinmap(viewpointmap_sub, mbl->m, BL_PC, st->oid, flag, mbl->x, mbl->y, mbl->id, color);
	return 0;
}

BUILDIN_FUNC(bg_getitem)
{
	int bg_id, nameid, amount, flag;

	bg_id = script_getnum(st, 2);
	nameid = script_getnum(st, 3);
	amount = script_getnum(st, 4);
	flag = script_getnum(st, 5);

	bg_team_getitem(bg_id, nameid, amount, flag);
	return 0;
}

BUILDIN_FUNC(bg_reward)
{
	int bg_id, nameid, amount, kafrapoints, quest_id, add_value, bg_arena, bg_result, fame;
	const char *var;

	bg_id = script_getnum(st, 2);
	nameid = script_getnum(st, 3);
	amount = script_getnum(st, 4);
	kafrapoints = script_getnum(st, 5);
	quest_id = script_getnum(st, 6);
	var = script_getstr(st, 7);
	add_value = script_getnum(st, 8);
	bg_arena = script_getnum(st, 9);
	bg_result = script_getnum(st, 10);
	fame = script_getnum(st, 11);

	bg_team_rewards(bg_id, nameid, amount, kafrapoints, quest_id, var, add_value, bg_arena, bg_result, fame);
	return 0;
}
/// Sets the bg_id of this npc.
///
/// flagemblem <bg_id>;
BUILDIN_FUNC(bg_flagemblem)
{
	TBL_NPC* nd;
	int bg_id = script_getnum(st,2);

	if(bg_id < 0)
		return SCRIPT_CMD_SUCCESS;

	nd = (TBL_NPC*)map_id2nd(st->oid);
	if( nd == NULL ) {
		ShowError("script:bg_flagemblem: npc %d not found\n", st->oid);
	} else if( nd->subtype != NPCTYPE_SCRIPT ) {
		ShowError("script:bg_flagemblem: unexpected subtype %d for npc %d '%s'\n", nd->subtype, st->oid, nd->exname);
	} else {
		bool changed = ( nd->u.scr.bg_id != bg_id )?true:false;
		nd->u.scr.bg_id = bg_id;
		clif_guild_emblem_area(&nd->bl);
	}
	return SCRIPT_CMD_SUCCESS;
}


// Extended Features BG [Easycore]
// For now, only used to add statistics
BUILDIN_FUNC(bg_rankpoints)
{
	TBL_PC *sd;
	int add_value, fame, type;

	if( !script_accid2sd(5,sd) )
		return SCRIPT_CMD_FAILURE;

	if(!sd)
		return SCRIPT_CMD_FAILURE;

	type = script_getnum(st,2);
	add_value = script_getnum(st,3);
	fame = script_getnum(st,4);

	if (type < BGR_FAME || type > BGR_MAX) {
		ShowError("buildin_bg_rankpoints: Unknown type \"%d\".\n", type);
		return SCRIPT_CMD_FAILURE;
	}

	if (fame)
		pc_addbgpoints(sd,fame);

	switch(type) {
		case BGR_FAME:
			if (!fame)
				pc_addbgpoints(sd,add_value);
			break;
		case BGR_SKULLS:
			add2limit(sd->status.bgstats.skulls,add_value,USHRT_MAX);
			break;
		case BGR_EOS_FLAGS:
			add2limit(sd->status.bgstats.eos_flags,add_value,USHRT_MAX);
			break;
		case BGR_SC_STOLE:
			add2limit(sd->status.bgstats.sc_stole,add_value,USHRT_MAX);
			break;
		case BGR_SC_CAPTURED:
			add2limit(sd->status.bgstats.sc_captured,add_value,USHRT_MAX);
			break;
		case BGR_SC_DROPPED:
			add2limit(sd->status.bgstats.sc_droped,add_value,USHRT_MAX);
			break;
		case BGR_CTF_TAKEN:
			add2limit(sd->status.bgstats.ctf_taken,add_value,USHRT_MAX);
			break;
		case BGR_CTF_CAPTURED:
			add2limit(sd->status.bgstats.ctf_captured,add_value,USHRT_MAX);
			break;
		case BGR_CTF_DROPPED:
			add2limit(sd->status.bgstats.sc_droped,add_value,USHRT_MAX);
			break;
		case BGR_DOM_BASES:
			add2limit(sd->status.bgstats.dom_bases,add_value,USHRT_MAX);
			break;
		case BGR_DOM_OFF_KILLS:
			add2limit(sd->status.bgstats.dom_off_kills,add_value,USHRT_MAX);
			break;
		case BGR_DOM_DEF_KILLS:
			add2limit(sd->status.bgstats.dom_def_kills,add_value,USHRT_MAX);
			break;
		case BGR_BARRICADE:
			add2limit(sd->status.bgstats.barricade_kill,add_value,USHRT_MAX);
			break;
		case BGR_EMPERIUM:
			add2limit(sd->status.bgstats.emperium_kill,add_value,USHRT_MAX);
			break;
		case BGR_GSTONE:
			add2limit(sd->status.bgstats.gstone_kill,add_value,USHRT_MAX);
			break;
		case BGR_RU_CAPTURES:
			add2limit(sd->status.bgstats.ru_captures,add_value,USHRT_MAX);
			break;
		case BGR_BOSS_FLAGS:
			add2limit(sd->status.bgstats.boss_flags,add_value,USHRT_MAX);
			break;
		case BGR_BOSS_KILLED:
			add2limit(sd->status.bgstats.boss_killed,add_value,USHRT_MAX);
			break;
		case BGR_TD_KILL:
			add2limit(sd->status.bgstats.td_kills,add_value,USHRT_MAX);
			break;
		case BGR_TD_DEATH:
			add2limit(sd->status.bgstats.td_deaths,add_value,USHRT_MAX);
			break;
	}

	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_rankpoints_area)
{
	const char *str;
	int m, x0, y0, x1, y1, bg_id;
	int add_value, type;
	int fame;

	bg_id = script_getnum(st,2);
	str = script_getstr(st,3);

	std::shared_ptr<s_battleground_data> bg = util::umap_find(bg_team_db, bg_id);

	if (!bg || (m = map_mapname2mapid(str)) < 0)
		return SCRIPT_CMD_SUCCESS;

	x0 = script_getnum(st,4);
	y0 = script_getnum(st,5);
	x1 = script_getnum(st,6);
	y1 = script_getnum(st,7);
	type = script_getnum(st,8);

	if (type < BGR_FAME || type > BGR_MAX) {
		ShowError("buildin_bg_rankpoints_area: Unknown type \"%d\".\n", type);
		return SCRIPT_CMD_FAILURE;
	}

	add_value = script_getnum(st,9);
	fame = script_getnum(st,10);
	for (const auto &member : bg->members) {
		if (member.sd->bl.m != m || member.sd->bl.x < x0 || member.sd->bl.y < y0 || member.sd->bl.x > x1 || member.sd->bl.y > y1)
			continue;

		if (fame)
			pc_addbgpoints(member.sd,fame);

		switch(type) {
			case BGR_FAME:
				if (!fame)
					pc_addbgpoints(member.sd,add_value);
				break;
			case BGR_SKULLS:
				add2limit(member.sd->status.bgstats.skulls,add_value,USHRT_MAX);
				break;
			case BGR_EOS_FLAGS:
				add2limit(member.sd->status.bgstats.eos_flags,add_value,USHRT_MAX);
				break;
			case BGR_SC_STOLE:
				add2limit(member.sd->status.bgstats.sc_stole,add_value,USHRT_MAX);
				break;
			case BGR_SC_CAPTURED:
				add2limit(member.sd->status.bgstats.sc_captured,add_value,USHRT_MAX);
				break;
			case BGR_SC_DROPPED:
				add2limit(member.sd->status.bgstats.sc_droped,add_value,USHRT_MAX);
				break;
			case BGR_CTF_TAKEN:
				add2limit(member.sd->status.bgstats.ctf_taken,add_value,USHRT_MAX);
				break;
			case BGR_CTF_CAPTURED:
				add2limit(member.sd->status.bgstats.ctf_captured,add_value,USHRT_MAX);
				break;
			case BGR_CTF_DROPPED:
				add2limit(member.sd->status.bgstats.sc_droped,add_value,USHRT_MAX);
				break;
			case BGR_DOM_BASES:
				add2limit(member.sd->status.bgstats.dom_bases,add_value,USHRT_MAX);
				break;
			case BGR_DOM_OFF_KILLS:
				add2limit(member.sd->status.bgstats.dom_off_kills,add_value,USHRT_MAX);
				break;
			case BGR_DOM_DEF_KILLS:
				add2limit(member.sd->status.bgstats.dom_def_kills,add_value,USHRT_MAX);
				break;
			case BGR_BARRICADE:
				add2limit(member.sd->status.bgstats.barricade_kill,add_value,USHRT_MAX);
				break;
			case BGR_EMPERIUM:
				add2limit(member.sd->status.bgstats.emperium_kill,add_value,USHRT_MAX);
				break;
			case BGR_GSTONE:
				add2limit(member.sd->status.bgstats.gstone_kill,add_value,USHRT_MAX);
				break;
			case BGR_RU_CAPTURES:
				add2limit(member.sd->status.bgstats.ru_captures,add_value,USHRT_MAX);
				break;
			case BGR_BOSS_FLAGS:
				add2limit(member.sd->status.bgstats.boss_flags,add_value,USHRT_MAX);
				break;
			case BGR_BOSS_KILLED:
				add2limit(member.sd->status.bgstats.boss_killed,add_value,USHRT_MAX);
				break;
			case BGR_TD_KILL:
				add2limit(member.sd->status.bgstats.td_kills,add_value,USHRT_MAX);
				break;
			case BGR_TD_DEATH:
				add2limit(member.sd->status.bgstats.td_deaths,add_value,USHRT_MAX);
				break;
		}
	}

	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_rankpoints_team)
{
	//const char *str;
	int bg_id;
	int type, add_value;
	int fame;

	bg_id = script_getnum(st,2);

	std::shared_ptr<s_battleground_data> bg = util::umap_find(bg_team_db, bg_id);

	if (!bg)
		return SCRIPT_CMD_SUCCESS;

	type = script_getnum(st,3);

	if (type < BGR_FAME || type > BGR_MAX) {
		ShowError("buildin_bg_rankpoints_area: Unknown type \"%d\".\n", type);
		return SCRIPT_CMD_FAILURE;
	}

	add_value = script_getnum(st,4);
	fame = script_getnum(st,5);
	for (const auto &member : bg->members) {

		if (fame)
			pc_addbgpoints(member.sd,fame);

		switch(type) {
			case BGR_FAME:
				if (!fame)
					pc_addbgpoints(member.sd,add_value);
				break;
			case BGR_SKULLS:
				add2limit(member.sd->status.bgstats.skulls,add_value,USHRT_MAX);
				break;
			case BGR_EOS_FLAGS:
				add2limit(member.sd->status.bgstats.eos_flags,add_value,USHRT_MAX);
				break;
			case BGR_SC_STOLE:
				add2limit(member.sd->status.bgstats.sc_stole,add_value,USHRT_MAX);
				break;
			case BGR_SC_CAPTURED:
				add2limit(member.sd->status.bgstats.sc_captured,add_value,USHRT_MAX);
				break;
			case BGR_SC_DROPPED:
				add2limit(member.sd->status.bgstats.sc_droped,add_value,USHRT_MAX);
				break;
			case BGR_CTF_TAKEN:
				add2limit(member.sd->status.bgstats.ctf_taken,add_value,USHRT_MAX);
				break;
			case BGR_CTF_CAPTURED:
				add2limit(member.sd->status.bgstats.ctf_captured,add_value,USHRT_MAX);
				break;
			case BGR_CTF_DROPPED:
				add2limit(member.sd->status.bgstats.sc_droped,add_value,USHRT_MAX);
				break;
			case BGR_DOM_BASES:
				add2limit(member.sd->status.bgstats.dom_bases,add_value,USHRT_MAX);
				break;
			case BGR_DOM_OFF_KILLS:
				add2limit(member.sd->status.bgstats.dom_off_kills,add_value,USHRT_MAX);
				break;
			case BGR_DOM_DEF_KILLS:
				add2limit(member.sd->status.bgstats.dom_def_kills,add_value,USHRT_MAX);
				break;
			case BGR_BARRICADE:
				add2limit(member.sd->status.bgstats.barricade_kill,add_value,USHRT_MAX);
				break;
			case BGR_EMPERIUM:
				add2limit(member.sd->status.bgstats.emperium_kill,add_value,USHRT_MAX);
				break;
			case BGR_GSTONE:
				add2limit(member.sd->status.bgstats.gstone_kill,add_value,USHRT_MAX);
				break;
			case BGR_RU_CAPTURES:
				add2limit(member.sd->status.bgstats.ru_captures,add_value,USHRT_MAX);
				break;
			case BGR_BOSS_FLAGS:
				add2limit(member.sd->status.bgstats.boss_flags,add_value,USHRT_MAX);
				break;
			case BGR_BOSS_KILLED:
				add2limit(member.sd->status.bgstats.boss_killed,add_value,USHRT_MAX);
				break;
			case BGR_TD_KILL:
				add2limit(member.sd->status.bgstats.td_kills,add_value,USHRT_MAX);
				break;
			case BGR_TD_DEATH:
				add2limit(member.sd->status.bgstats.td_deaths,add_value,USHRT_MAX);
				break;
		}
	}

	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_queue_info)
{
	int queue_id, flag;
	queue_id = script_getnum(st, 2);
	flag = script_getnum(st, 3);

	std::shared_ptr<s_battleground_queue> queue;
	if ((queue = bg_search_queue_id(queue_id)) == nullptr) {
		ShowError("buildin_bg_queue_info: Unknown queue id %d.\n", queue_id);
		return SCRIPT_CMD_FAILURE;
	}

	std::shared_ptr<s_battleground_type> bg;
	if ((bg = battleground_db.find(queue_id)) == nullptr) {
		ShowError("buildin_bg_queue_info: Unknown battleground id %d.\n", queue_id);
		return SCRIPT_CMD_FAILURE;
	}

	switch(flag) {
		case 0: script_pushstrcopy(st, bg->name.c_str()); break;
		case 1: script_pushint(st, bg->required_players); break;
		case 2: script_pushint(st, queue->id); break;
		case 3: script_pushint(st, queue->teama_members.size()+queue->teamb_members.size()); break;
		default:
			ShowError("buildin_bg_queue_info: Unknown flag type %d.\n", flag);
			return SCRIPT_CMD_FAILURE;
	}

	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_set_data)
{
	int queue_id, type, val1, val2;
	queue_id = script_getnum(st, 2);

	std::shared_ptr<s_battleground_queue> queue;
	if ((queue = bg_search_queue_id(queue_id)) == nullptr) {
		ShowError("buildin_bg_set_data: Unknown queue id %d.\n", queue_id);
		return SCRIPT_CMD_FAILURE;
	}

	std::shared_ptr<s_battleground_type> bg;
	if ((bg = battleground_db.find(queue_id)) == nullptr) {
		ShowError("buildin_bg_set_data: Unknown battleground id %d.\n", queue_id);
		return SCRIPT_CMD_FAILURE;
	}
	type = script_getnum(st, 3);
	val1 = script_getnum(st, 4);
	val2 = script_getnum(st, 5);

	switch(type) {
		case 0:
			if (val1 < 1) {
				ShowError("buildin_bg_set_data: val1 cannot be lower than 1.\n");
				return SCRIPT_CMD_FAILURE;
			}
			bg->required_players = val1;
			break;
		default:
			ShowError("buildin_bg_set_data: Unknown type type %d.\n", type);
			return SCRIPT_CMD_FAILURE;
	}
	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_queue_finish)
{
	int queue_id= script_getnum(st,2);

	std::shared_ptr<s_battleground_queue> queue;
	if ((queue = bg_search_queue_id(queue_id)) == nullptr) {
		ShowError("buildin_bg_queue_info: Unknown queue id %d.\n", queue_id);
		return SCRIPT_CMD_FAILURE;
	}
	bg_queue_clear(queue,true);
	return SCRIPT_CMD_SUCCESS;
}

/*==========================================
 * Reset battle rank
 * type :
 *	1 : Battleground Rank
 *	2 : War of Emperium Rank
 *------------------------------------------*/
BUILDIN_FUNC(battle_rank_reset)
{
	int type = script_getnum(st,2);

	if (type < 1 && type > 2)
		return SCRIPT_CMD_FAILURE;

	if (type == 1)
		type = RANK_BG;
	else
		type = RANK_WOE;

	pc_rank_reset(type);
	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_set_cemetery)
{
	int bg_id,x,y,mapindex;
	const char* str;
	bg_id = script_getnum(st, 2);
	str = script_getstr(st,3);
	x = script_getnum(st,4);
	y = script_getnum(st,5);

	std::shared_ptr<s_battleground_data> bg = util::umap_find(bg_team_db, bg_id);
	if (!bg)
		return SCRIPT_CMD_FAILURE;

	mapindex = mapindex_name2id(str);
	if (!mapindex)// Invalid map
		return SCRIPT_CMD_FAILURE;

	bg->cemetery.map = mapindex;
	bg->cemetery.x = x;
	bg->cemetery.y = y;

	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_announce)
{
	const char *mes = script_getstr(st, 2);
	const char *fontColor = script_hasdata(st, 3) ? script_getstr(st, 3) : "0xFFFFFF";
	int         fontType = script_hasdata(st, 4) ? script_getnum(st, 4) : 0x190; // default fontType (FW_NORMAL)
	int         fontSize = script_hasdata(st, 5) ? script_getnum(st, 5) : 12;    // default fontSize
	int         fontAlign = script_hasdata(st, 6) ? script_getnum(st, 6) : 0;     // default fontAlign
	int         fontY = script_hasdata(st, 7) ? script_getnum(st, 7) : 0;     // default fontY

	clif_broadcast2(NULL, mes, (int)strlen(mes) + 1, strtol(fontColor, (char **)NULL, 0), fontType, fontSize, fontAlign, fontY, BG_LISTEN);
	return SCRIPT_CMD_SUCCESS;
}

/*==========================================
 * Return fame rank position
 * return by @num :
 *	0 : Battleground Rank
 *	1 : War of Emperium Rank
 *------------------------------------------*/
BUILDIN_FUNC(getcharrank)
{
	int num;
	TBL_PC *sd;

	num = script_getnum(st,2);

	if( !script_charid2sd(3,sd) ){
		script_pushint(st,-1); //return 0, according docs
		return SCRIPT_CMD_SUCCESS;
	}

	switch( num ) {
	case 0: script_pushint(st,pc_famerank(sd->status.char_id, -1)); break;
	case 1: script_pushint(st,pc_famerank(sd->status.char_id, -2)); break;
	default:
		ShowError("buildin_getcharrank: invalid parameter (%d).\n", num);
		script_pushint(st,0);
		break;
	}
	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_soundeffect)
{
	int bg_id = script_getnum(st,3);
	std::shared_ptr<s_battleground_data> bg = util::umap_find(bg_team_db, bg_id);

	if (bg == nullptr) {
		ShowError("buildin_bg_soundeffect: unexistent bg team (%d).\n", bg_id);
		return SCRIPT_CMD_SUCCESS;
	}
	const char* name = script_getstr(st,2);

	for (const auto &member : bg->members)
		clif_soundeffect(member.sd->bl, name, 0, SELF);

	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_specialeffect)
{
	int bg_id = script_getnum(st,3);
	std::shared_ptr<s_battleground_data> bg = util::umap_find(bg_team_db, bg_id);

	if (bg == nullptr) {
		ShowError("buildin_bg_specialeffect: unexistent bg team (%d).\n", bg_id);
		return SCRIPT_CMD_SUCCESS;
	}
	int type = script_getnum(st,2);

	for (const auto &member : bg->members)
		clif_specialeffect(&member.sd->bl, type, AREA);

	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_emotion)
{
	int bg_id = script_getnum(st,3);
	std::shared_ptr<s_battleground_data> bg = util::umap_find(bg_team_db, bg_id);

	if (bg == nullptr) {
		ShowError("buildin_bg_specialeffect: unexistent bg team (%d).\n", bg_id);
		return SCRIPT_CMD_SUCCESS;
	}
	int type = script_getnum(st,2);

	if (type < ET_SURPRISE || type >= ET_MAX) {
		ShowWarning("buildin_bg_emotion: Unknown emotion %d (min=%d, max=%d).\n", type, ET_SURPRISE, (ET_MAX-1));
		return SCRIPT_CMD_SUCCESS;
	}

	for (const auto &member : bg->members)
		clif_emotion(member.sd->bl, static_cast<emotion_type>(type));

	return SCRIPT_CMD_SUCCESS;
}


BUILDIN_FUNC(bg_sc_end)
{
	int bg_id = script_getnum(st,3);
	std::shared_ptr<s_battleground_data> bg = util::umap_find(bg_team_db, bg_id);

	if (bg == nullptr) {
		ShowError("buildin_bg_sc_end: unexistent bg team (%d).\n", bg_id);
		return SCRIPT_CMD_SUCCESS;
	}
	int type = script_getnum(st,2);

	if (type > SC_NONE && type < SC_MAX) {
		std::shared_ptr<s_status_change_db> sc_db = status_db.find( type );

		if( sc_db == nullptr ){
			ShowError( "buildin_bg_sc_end: Unknown status change %d.\n", type );
			return SCRIPT_CMD_FAILURE;
		}

		if (sc_db->flag[SCF_NOCLEARBUFF] && sc_db->flag[SCF_NOFORCEDEND]) {
			ShowError( "buildin_bg_sc_end: Status %d cannot be cleared.\n", type );
			return SCRIPT_CMD_FAILURE;
		}

		for (const auto &member : bg->members)
			status_change_end(&member.sd->bl, (sc_type)type);
	} else {
		for (const auto &member : bg->members)
			status_change_clear(&member.sd->bl, 3); // remove all effects
	}

	return SCRIPT_CMD_SUCCESS;
}

/* Starts a status effect on the target unit or on the attached player.
 *
 * bg_sc_start  <bg_team_id>,<effect_id>,<duration>,<val1>{,<rate>,<flag>,{<unit_id>}};
 * bg_sc_start2 <bg_team_id>,<effect_id>,<duration>,<val1>,<val2>{,<rate,<flag>,{<unit_id>}};
 * bg_sc_start4 <bg_team_id>,<effect_id>,<duration>,<val1>,<val2>,<val3>,<val4>{,<rate,<flag>,{<unit_id>}};
 * <flag>: enum e_status_change_start_flags
 */
BUILDIN_FUNC(bg_sc_start)
{
	int bg_id = script_getnum(st,2);
	std::shared_ptr<s_battleground_data> bg = util::umap_find(bg_team_db, bg_id);

	if (bg == nullptr) {
		ShowError("buildin_bg_sc_end: unexistent bg team (%d).\n", bg_id);
		return SCRIPT_CMD_SUCCESS;
	}

	enum sc_type type;
	int tick, val1, val2, val3, val4=0, rate, flag;
	char start_type;
	const char* command = script_getfuncname(st);

	if(strstr(command, "4"))
		start_type = 4;
	else if(strstr(command, "2"))
		start_type = 2;
	else
		start_type = 1;

	type = (sc_type)script_getnum(st,3);
	tick = script_getnum(st,4);
	val1 = script_getnum(st,5);
	flag = script_hasdata(st,6+start_type)?script_getnum(st,6+start_type):SCSTART_NOAVOID;
	rate = script_hasdata(st,5+start_type)?min(script_getnum(st,5+start_type),10000):10000;

	uint16 skill_id;

	if(tick == 0 && val1 > 0 && type > SC_NONE && type < SC_MAX && (skill_id = status_db.getSkill(type)) > 0)
	{// When there isn't a duration specified, try to get it from the skill_db
		tick = skill_get_time(skill_id, val1);
	}

	switch(start_type) {
		case 1:
			for (const auto &member : bg->members)
				status_change_start(&member.sd->bl, &member.sd->bl, type, rate, val1, 0, 0, val4, tick, flag);
			break;
		case 2:
			val2 = script_getnum(st,6);
			for (const auto &member : bg->members)
				status_change_start(&member.sd->bl, &member.sd->bl, type, rate, val1, val2, 0, val4, tick, flag);
			break;
		case 4:
			val2 = script_getnum(st,6);
			val3 = script_getnum(st,7);
			val4 = script_getnum(st,8);
			for (const auto &member : bg->members)
				status_change_start(&member.sd->bl, &member.sd->bl, type, rate, val1, val2, val3, val4, tick, flag);
			break;
	}
	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_percentheal)
{
	int bg_id = script_getnum(st,2);
	std::shared_ptr<s_battleground_data> bg = util::umap_find(bg_team_db, bg_id);

	if (bg == nullptr) {
		ShowError("buildin_bg_sc_end: unexistent bg team (%d).\n", bg_id);
		return SCRIPT_CMD_SUCCESS;
	}

	int hp = script_getnum(st,3);
	int sp = script_getnum(st,4);

	for (const auto &member : bg->members) {
		if (member.sd->sc.getSCE(SC_NORECOVER_STATE))
			continue;
		pc_percentheal(member.sd,hp,sp);
	}
	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_team_leave)
{
	int bg_id = script_getnum(st,2);
	std::shared_ptr<s_battleground_data> bg = util::umap_find(bg_team_db, bg_id);

	if (bg == nullptr) {
		ShowError("buildin_bg_team_leave: unexistent bg team (%d).\n", bg_id);
		return SCRIPT_CMD_SUCCESS;
	}

	for (const auto &member : bg->members)
		bg_team_leave(member.sd, false, false);
	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_clear_buffs)
{
	int bg_id = script_getnum(st,2);
	std::shared_ptr<s_battleground_data> bg = util::umap_find(bg_team_db, bg_id);
	if (bg == nullptr) {
		ShowError("buildin_bg_clear_buffs: unexistent bg team (%d).\n", bg_id);
		return SCRIPT_CMD_SUCCESS;
	}
	uint8 type = script_getnum(st,3);

	for (const auto &member : bg->members)
		status_change_clear_buffs(&member.sd->bl, type);
	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_clear_buffs_area)
{
	int bg_id = script_getnum(st,2);
	const char *str = script_getstr(st,4);
	int m, x0, y0, x1, y1;

	std::shared_ptr<s_battleground_data> bg = util::umap_find(bg_team_db, bg_id);
	if (bg == nullptr) {
		ShowError("buildin_bg_clear_buffs_area: unexistent bg team (%d).\n", bg_id);
		return SCRIPT_CMD_SUCCESS;
	}
	if ((m = map_mapname2mapid(str)) < 0) {
		ShowError("buildin_bg_clear_buffs_area: unexistent map (%s).\n", str);
		return SCRIPT_CMD_SUCCESS;
	}

	uint8 type = script_getnum(st,3);
	x0 = script_getnum(st,5);
	y0 = script_getnum(st,6);
	x1 = script_getnum(st,7);
	y1 = script_getnum(st,8);

	for (const auto &member : bg->members) {
		if (member.sd->bl.m != m || member.sd->bl.x < x0 || member.sd->bl.y < y0 || member.sd->bl.x > x1 || member.sd->bl.y > y1)
			continue;
		status_change_clear_buffs(&member.sd->bl, type);
	}
	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(bg_warp_cemetery)
{
	int bg_id= script_getnum(st,2);

	std::shared_ptr<s_battleground_data> bg = util::umap_find(bg_team_db, bg_id);
	if (bg == nullptr) {
		ShowError("buildin_bg_warp_cemetery: unexistent bg team (%d).\n", bg_id);
		return SCRIPT_CMD_SUCCESS;
	}

	bg_team_warp(bg_id, bg->cemetery.map, bg->cemetery.x, bg->cemetery.y);
	return SCRIPT_CMD_SUCCESS;
}

/*==========================================
 *------------------------------------------*/
BUILDIN_FUNC(donpceventall)
{
	const char* event = script_getstr(st,2);
	npc_event_doall(event);
	return SCRIPT_CMD_SUCCESS;
}
