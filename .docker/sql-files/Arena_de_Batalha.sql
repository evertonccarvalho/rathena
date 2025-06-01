-- Tabela para ranking PvP (atualizada)
CREATE TABLE IF NOT EXISTS `ranking_pvp` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `account_id` int(11) NULL DEFAULT NULL,
  `char_id` int(11) NOT NULL,
  `char_name` varchar(255) NOT NULL,
  `Matou` int(11) NOT NULL DEFAULT '0',
  `Morreu` int(11) NOT NULL DEFAULT '0',
  `Total` int(11) NOT NULL DEFAULT '0',
  `last_kill` datetime DEFAULT NULL,
  `last_killed_char` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `char_id` (`char_id`),
  KEY `account_id` (`account_id`),
  KEY `Total` (`Total`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- Tabela para ranking GvG (atualizada)
CREATE TABLE IF NOT EXISTS `ranking_gvg` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `guild_id` int(11) NOT NULL,
  `guild_name` varchar(255) NOT NULL,
  `Matou` int(11) NOT NULL DEFAULT '0',
  `Morreu` int(11) NOT NULL DEFAULT '0',
  `Total` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `guild_id` (`guild_id`),
  KEY `Total` (`Total`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- Tabela para registro de resets do ranking PvP (atualizada)
CREATE TABLE IF NOT EXISTS `ranking_pvp_reset` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `account_id` int(11) NULL DEFAULT NULL,
  `char_id` int(11) NOT NULL,
  `Data` varchar(255) NOT NULL,
  `Premio?` enum('Sim','N�o') NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- Tabela para registro de resets do ranking GvG (atualizada)
CREATE TABLE IF NOT EXISTS `ranking_gvg_reset` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `account_id` int(11) NULL DEFAULT NULL,
  `char_id` int(11) NOT NULL,
  `Data` varchar(255) NOT NULL,
  `Premio?` enum('Sim','N�o') NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;


CREATE TABLE IF NOT EXISTS `ranking_pvp_logs` (
  `id` INT AUTO_INCREMENT PRIMARY KEY,
  `Assassino` VARCHAR(30) NOT NULL,
  `Alvo` VARCHAR(30) NOT NULL,
  `Data` VARCHAR(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
