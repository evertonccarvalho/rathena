CREATE TABLE IF NOT EXISTS `rotd_system` (
  `race` varchar(20) NOT NULL,
  `race_id` int(11) NOT NULL,
  `zeny` int(11) NOT NULL,
  `win` int(11) NOT NULL,
  `week` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

INSERT INTO `rotd_system` (`race`, `race_id`, `zeny`, `win`, `week`) VALUES
('Amorfo', 5, 0, 0, 0),
('Morto-Vivo', 1, 0, 0, 0),
('Bruto', 2, 0, 0, 0),
('Planta', 3, 0, 0, 0),
('Inseto', 4, 0, 0, 0),
('Peixe', 5, 0, 0, 0),
('Dêmonio', 6, 0, 0, 0),
('Humanóide', 7, 0, 0, 0),
('Dragão', 9, 0, 0, 0),
('Anjo', 8, 0, 0, 0),
('Total', 10, 0, 0, 0);

CREATE TABLE IF NOT EXISTS `rotd_control` (
  `ID` int(11) NOT NULL,
  `RID` int(11) NOT NULL,
  `bonus` int(11) NOT NULL,
  `total_zeny` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

INSERT INTO `rotd_control` (`ID`, `RID`, `bonus`, `total_zeny`) VALUES
(1, 0, 73, 0);

CREATE TABLE `roth_logs` (
  `nome` varchar(30) NOT NULL,
  `zeny` int(100) NOT NULL,
  `elemento` varchar(30) NOT NULL,
  `data` varchar(13) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `rotd_time` (
  `id` int(11) NOT NULL,
  `time` int(15) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

INSERT INTO `rotd_time` (`id`, `time`) VALUES
(1, 1652171379);

