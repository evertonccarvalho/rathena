
CREATE TABLE IF NOT EXISTS `ranking_pvp` (
  `char_id` int(11) NOT NULL,
  `char_name` varchar(24) NOT NULL,
  `Matou` int(10) DEFAULT '0',
  `Morreu` int(10) DEFAULT '0',
  `Total` int(10) DEFAULT '0',
  PRIMARY KEY (`char_id`)
) ENGINE=MyISAM;

CREATE TABLE IF NOT EXISTS `ranking_gvg` (
  `guild_id` int(11) NOT NULL,
  `char_id` int(11) NOT NULL,
  `guild_name` varchar(24) NOT NULL,
  `Matou` int(10) DEFAULT '0',
  `Morreu` int(10) DEFAULT '0',
  `Total` int(10) DEFAULT '0',
  PRIMARY KEY (`guild_id`)
) ENGINE=MyISAM;

CREATE TABLE IF NOT EXISTS `ranking_pvp_logs` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `Assassino` varchar(32) DEFAULT '0',
  `Alvo` varchar(32) DEFAULT '0',
  `Data` varchar(32) DEFAULT '0',
  PRIMARY KEY (`ID`)
) ENGINE=MyISAM;

CREATE TABLE `ranking_pvp_reset` (
  `account_id` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `char_id` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `Data` varchar(32) DEFAULT '0',
  `Premio?` varchar(32) DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

CREATE TABLE `ranking_gvg_reset` (
  `account_id` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `char_id` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `Data` varchar(32) DEFAULT '0',
  `Premio?` varchar(32) DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

