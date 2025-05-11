CREATE TABLE `mvp` (
  `char_id` int(11) unsigned NOT NULL auto_increment,
  `account_id` int(11) unsigned NOT NULL default '0',
  `name` varchar(255) NOT NULL default '0',
  `mvps` int(11) unsigned NOT NULL default '0',
  `pontos` int(11) unsigned NOT NULL default '0',
  `premio_mvp` INT (11) NOT NULL DEFAULT '0',
  KEY `char_id` (`char_id`),
  KEY `account_id` (`account_id`),
  KEY `mvps` (`mvps`),
  KEY `pontos` (`pontos`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
