// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Atcommands
 * Place the body of custom atcommands in this file.
 * Format:
 *	ACMD_FUNC(command_name)
 *	{
 *		<code>;
 *	}
 **/

//ACMD_FUNC(newcommand)
//{
//	clif_displaymessage(fd, "It works!");
//	clif_specialeffect(&sd->bl, EF_HEARTCASTING, AREA);
//	return 0;
//}


/*==========================================
 * Guild Skill Usage for Guild Masters
 *------------------------------------------*/
ACMD_FUNC(guildskill)
{
	int i, skillnum = 0, skill_lv = 0;
	t_tick tick = gettick();

	const struct { char skillstr[3]; int id; } skills[] = {
		{ "BO",	10010 },
		{ "RG",	10011 },
		{ "RS",	10012 },
		{ "EC",	10013 },
	};

	// Check for Skill ID
	for(i = 0; i < ARRAYLENGTH(skills); i++) {
		if( strncmpi(message, skills[i].skillstr, 3) == 0 )
		{
			skillnum = skills[i].id;
			break;
		}
	}
	if (!skillnum) {
		clif_displaymessage(fd, msg_txt(sd, 2012)); // Unknown skill. Use @guildskill EC/RS/RG/BO
		return -1;
	}

	if( !map_getmapflag(sd->bl.m, MF_BATTLEGROUND) ) {
		if( sd->state.gmaster_flag )
			skill_lv = guild_checkskill(sd->guild->guild, skillnum);
		else {
			clif_displaymessage(fd, msg_txt(sd, 2013)); // This command is reserved for Guild Leaders.
			return -1;
		}
	} else {
		std::shared_ptr<s_battleground_data> bg = util::umap_find(bg_team_db, sd->bg_id);
		if(bg && bg->leader_char_id == sd->status.char_id)
			skill_lv = bg_checkskill(bg.get(), skillnum);
		else {
			clif_displaymessage(fd, msg_txt(sd, 2014)); // This command is reserved for Team Leaders.
			return -1;
		}
	}

	if (pc_cant_act(sd) || pc_issit(sd) || skill_isNotOk(skillnum, *sd) || sd->ud.skilltimer != -1 || sd->sc.option&(OPTION_WEDDING|OPTION_XMAS|OPTION_SUMMER) || sd->sc.getSCE(SC_BASILICA))
		return -1;

	if (DIFF_TICK(tick, sd->ud.canact_tick) < 0)
		return -1;

	if (sd->menuskill_id) {
		if (sd->menuskill_id == SA_TAMINGMONSTER)
			sd->menuskill_id = sd->menuskill_val = 0; //Cancel pet capture.
		else if (sd->menuskill_id != SA_AUTOSPELL)
			return -1; //Can't use skills while a menu is open.
	}

	sd->skillitem = sd->skillitemlv = 0;
	if (skill_lv != 0)
		unit_skilluse_id(&sd->bl, sd->bl.id, skillnum, skill_lv);
	return 0;
}

/*==========================================
 * Guild Skill Info Usage
 *------------------------------------------*/
ACMD_FUNC(guildskillinfo)
{
	char output[CHAT_SIZE_MAX];
	if (!(sd->bg_id || sd->guild)) {
		clif_displaymessage(fd, msg_txt(sd, 2015)); // You need to be in a Guild or in a Battleground Arena.
		return -1;
	}

	clif_displaymessage(fd, "=== Guild Skills Cooldown ===.");
	if (guild_skills_timer(sd,10013) > 0) {
		snprintf(output, sizeof(output), msg_txt(sd, 2016), guild_skills_timer(sd,10013)); // EC: %d seconds
		clif_displaymessage(fd, output);
	} else
		clif_displaymessage(fd, msg_txt(sd, 2017)); // EC: Ready to use!

	if (guild_skills_timer(sd,10010) > 0) {
		snprintf(output, sizeof(output), msg_txt(sd, 2018), guild_skills_timer(sd,10010)); // BO: %d seconds
		clif_displaymessage(fd, output);
	} else
		clif_displaymessage(fd, msg_txt(sd, 2019)); // BO: Ready to use!

	if (guild_skills_timer(sd,10011) > 0) {
		snprintf(output, sizeof(output), msg_txt(sd, 2020), guild_skills_timer(sd,10011)); // RG: %d seconds
		clif_displaymessage(fd, output);
	} else
		clif_displaymessage(fd, msg_txt(sd, 2021)); // RG: Ready to use!

	if (guild_skills_timer(sd,10012) > 0) {
		snprintf(output, sizeof(output), msg_txt(sd, 2022), guild_skills_timer(sd,10012)); // RS: %d seconds
		clif_displaymessage(fd, output);
	} else
		clif_displaymessage(fd, msg_txt(sd, 2023)); // RS: Ready to use!

	return 0;
}

ACMD_FUNC(leader)
{
	map_session_data *pl_sd;
	nullpo_retr(-1,sd);
	if( !sd->state.bmaster_flag )
		clif_displaymessage(fd, msg_txt(sd, 2014)); // This command is reserved for Team Leaders.
	else if( sd->ud.skilltimer != INVALID_TIMER )
		clif_displaymessage(fd, msg_txt(sd,2024)); // Command cannot be used while casting a skill.
	else if( !message || !*message )
		clif_displaymessage(fd, msg_txt(sd,2025)); // Please enter the name of the new Leader (usage: @leader <name>).
	else if( (pl_sd = map_nick2sd((char *)message,false)) == NULL )
		clif_displaymessage(fd, msg_txt(sd,3)); // Character not found.
	else if( sd->bg_id != pl_sd->bg_id )
		clif_displaymessage(fd, msg_txt(sd,2026)); // The player is not part of your Team.
	else if( sd == pl_sd )
		clif_displaymessage(fd, msg_txt(sd,2027)); // You are already the Team Leader.
	else { // Everytest OK!
		std::shared_ptr<s_battleground_data> bgteam = util::umap_find(bg_team_db, sd->bg_id);
		if (!bgteam)
			return -1;

		sprintf(atcmd_output, msg_txt(NULL,2028), pl_sd->status.name); // Team Leader transfered to [%s]
		clif_broadcast2(&sd->bl, atcmd_output, (int)strlen(atcmd_output)+1, bgteam->color, 0x190, 20, 0, 0, BG);

		bgteam->leader_char_id = pl_sd->status.char_id;
		pl_sd->state.bmaster_flag = 1;
		sd->state.bmaster_flag = 0;

		clif_name_area(&sd->bl);
		clif_name_area(&pl_sd->bl);
		return 0;
	}
	return -1;
}

ACMD_FUNC(reportafk)
{
	map_session_data *pl_sd;
	nullpo_retr(-1,sd);
	if( !sd->bg_id )
		clif_displaymessage(fd, msg_txt(sd, 2029)); // This command is reserved for Battleground
	else if( !sd->state.bmaster_flag && battle_config.bg_reportafk_leaderonly )
		clif_displaymessage(fd, msg_txt(sd, 2014)); // This command is reserved for Team Leaders.
	else if( !message || !*message )
		clif_displaymessage(fd, msg_txt(sd, 2030)); // Please enter the AFK player's nick (usage: @reportafk <name>).
	else if( (pl_sd = map_nick2sd((char *)message,false)) == NULL )
		clif_displaymessage(fd, msg_txt(sd,3)); // Character not found.
	else if( sd->bg_id != pl_sd->bg_id )
		clif_displaymessage(fd, msg_txt(sd,2026)); // The player is not part of your Team.
	else if( sd == pl_sd )
		clif_displaymessage(fd, msg_txt(sd,2031)); // You cannot report yourself.
	else if( pl_sd->state.bg_afk == 0 )
		clif_displaymessage(fd, msg_txt(sd,2032)); // The player is not AFK in this Battleground
	else { // Everytest OK!
		std::shared_ptr<s_battleground_data> bg = util::umap_find(bg_team_db, sd->bg_id);
		if(!bg)
			return -1;

		bg_team_leave(pl_sd, true, true);
		clif_displaymessage(pl_sd->fd, msg_txt(sd,2001)); // You have been kicked from Battleground for your AFK status
		pc_setpos(pl_sd,mapindex_name2id(pl_sd->status.save_point.map),pl_sd->status.save_point.x,pl_sd->status.save_point.y,CLR_OUTSIGHT);
		clif_refresh(pl_sd);

		sprintf(atcmd_output, msg_txt(sd, 2034), pl_sd->status.name); // - AFK [%s] Kicked -
		clif_broadcast2(&sd->bl, atcmd_output, (int)strlen(atcmd_output)+1, bg->color, 0x190, 20, 0, 0, BG);
		return 0;
	}
	return -1;
}

ACMD_FUNC(listenbg)
{
	sd->state.bg_listen = (sd->state.bg_listen == 0);

	if( sd->state.bg_listen )
		clif_displaymessage(fd, msg_txt(sd,2035)); // You no longer will receive announces from Battleground
	else
		clif_displaymessage(fd, msg_txt(sd,2036)); // You will receive announces from Battleground

	return 0;
}

ACMD_FUNC(order)
{
	nullpo_retr(-1,sd);
	if (!message || !*message) {
		clif_displaymessage(fd, msg_txt(sd,2037)); // Please write a message (usage: @order <message>).
		return -1;
	}

	if (map_getmapflag(sd->bl.m, MF_BATTLEGROUND)) {
		if( !sd->state.bmaster_flag )
		{
			clif_displaymessage(fd, msg_txt(sd,2014)); // This command is reserved for Team Leaders.
			return -1;
		}
		std::shared_ptr<s_battleground_data> bgteam = util::umap_find(bg_team_db, sd->bg_id);
		if (!bgteam)
			return -1;

		clif_broadcast2(&sd->bl, message, (int)strlen(message)+1, bgteam->color, 0x190, 20, 0, 0, BG);
	}
	else {
		if (!sd->state.gmaster_flag) {
			clif_displaymessage(fd, msg_txt(sd, 2013)); // This command is reserved for Guild Leaders.
			return -1;
		}
		clif_broadcast2(&sd->bl, message, (int)strlen(message)+1, 0xFF0000, 0x190, 20, 0, 0, GUILD);
	}

	return 0;
}

ACMD_FUNC(bgrank)
{
	int i;

	clif_messagecolor(&sd->bl, color_table[COLOR_LIGHT_GREEN], "============ BATTLEGROUND RANK ============", false, SELF);
	for( i = 0; i < MAX_FAME_LIST; i++ )
	{
		if (!bg_fame_list[i].id)
			sprintf(atcmd_output,"[ %d ] None        :    0 POINT",i+1);
		else
			sprintf(atcmd_output,"[ %d ] %s        :    %d POINT",i+1,bg_fame_list[i].name,bg_fame_list[i].fame);
		clif_messagecolor(&sd->bl, color_table[COLOR_LIGHT_GREEN], atcmd_output, false, SELF);
	}
	sprintf(atcmd_output,"MY POINT    :    %d POINT",sd->status.bgstats.points);
	clif_messagecolor(&sd->bl, color_table[COLOR_LIGHT_GREEN], "===========================================", false, SELF);
	clif_messagecolor(&sd->bl, color_table[COLOR_LIGHT_GREEN], atcmd_output, false, SELF);
	clif_messagecolor(&sd->bl, color_table[COLOR_LIGHT_GREEN], "===========================================", false, SELF);
	return 0;
}

ACMD_FUNC(woerank)
{
	int i;

	clif_messagecolor(&sd->bl, color_table[COLOR_CYAN], "============ WAR OF EMPERIUM RANK ============", false, SELF);
	for( i = 0; i < MAX_FAME_LIST; i++ )
	{
		if (!woe_fame_list[i].id)
			sprintf(atcmd_output,"[ %d ] None        :    0 POINT",i+1);
		else
			sprintf(atcmd_output,"[ %d ] %s        :    %d POINT",i+1,woe_fame_list[i].name,woe_fame_list[i].fame);
		clif_messagecolor(&sd->bl, color_table[COLOR_CYAN], atcmd_output, false, SELF);
	}
	sprintf(atcmd_output,"MY POINT    :    %d POINT",sd->status.wstats.points);
	clif_messagecolor(&sd->bl, color_table[COLOR_CYAN], "===========================================", false, SELF);
	clif_messagecolor(&sd->bl, color_table[COLOR_CYAN], atcmd_output, false, SELF);
	clif_messagecolor(&sd->bl, color_table[COLOR_CYAN], "===========================================", false, SELF);
	return 0;
}
