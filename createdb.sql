

CREATE DATABASE `db2` /*!40100 DEFAULT CHARACTER SET utf8 */;

USE db2;

CREATE TABLE IF NOT EXISTS `platoons` (
  `id_platoons` int(11) NOT NULL AUTO_INCREMENT,
  `year` year(4) NOT NULL,
  `count_man` int(11) NOT NULL,
  `number_of_stream` int(11) NOT NULL,
  `count_half_platoons` int(11) NOT NULL,
  `vus` int(11) NOT NULL,
  PRIMARY KEY (`id_platoons`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `class_type` (
  `id_class_type` int(11) NOT NULL,
  `name` varchar(45) NOT NULL,
  PRIMARY KEY (`id_class_type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `professors` (
  `id_professors` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  PRIMARY KEY (`id_professors`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `extra_duty` (
  `id_extra_duty` int(11) NOT NULL AUTO_INCREMENT,
  `duty_name` varchar(45) DEFAULT NULL,
  `hours` int(11) NOT NULL,
  `position_name` varchar(45) DEFAULT NULL,
  `id_professors` int(11) NOT NULL,
  PRIMARY KEY (`id_extra_duty`),
  KEY `id_professors_idx` (`id_professors`),
  CONSTRAINT `id_professors` FOREIGN KEY (`id_professors`) REFERENCES `professors` (`id_professors`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `disciplines` (
  `id_disciplines` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  PRIMARY KEY (`id_disciplines`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `thematic_plan` (
  `id_thematic_plan` int(11) NOT NULL AUTO_INCREMENT,
  `vk_uvc` int(10) unsigned NOT NULL,
  `id_disciplines` int(11) NOT NULL,
  `id_platoons` int(11) NOT NULL,
  `semester` int(11) NOT NULL,
  PRIMARY KEY (`id_thematic_plan`),
  KEY `id_platoons_idx` (`id_platoons`),
  KEY `id_disciplines_idx` (`id_disciplines`),
  CONSTRAINT `id_disciplines` FOREIGN KEY (`id_disciplines`) REFERENCES `disciplines` (`id_disciplines`) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT `id_platoons` FOREIGN KEY (`id_platoons`) REFERENCES `platoons` (`id_platoons`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `classes` (
  `id_classes` int(11) NOT NULL AUTO_INCREMENT,
  `number` int(10) unsigned NOT NULL,
  `id_type` int(11) NOT NULL,
  `hours` int(10) unsigned NOT NULL,
  `id_thematic_plan` int(11) NOT NULL,
  PRIMARY KEY (`id_classes`),
  KEY `id_type_idx` (`id_type`),
  KEY `id_thematic_plan_idx` (`id_thematic_plan`),
  CONSTRAINT `id_thematic_plan` FOREIGN KEY (`id_thematic_plan`) REFERENCES `thematic_plan` (`id_thematic_plan`) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT `id_type` FOREIGN KEY (`id_type`) REFERENCES `class_type` (`id_class_type`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `classes_professors` (
  `id_classes_professors` int(11) NOT NULL AUTO_INCREMENT,
  `id_classes` int(11) NOT NULL,
  `first_classes` int(11) NOT NULL,
  `id_professors` int(11) NOT NULL,
  PRIMARY KEY (`id_classes_professors`),
  KEY `professors_id_idx` (`id_professors`),
  KEY `classes_id_idx` (`id_classes`),
  CONSTRAINT `classes_id` FOREIGN KEY (`id_classes`) REFERENCES `classes` (`id_classes`) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT `professors_id` FOREIGN KEY (`id_professors`) REFERENCES `professors` (`id_professors`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=48 DEFAULT CHARSET=utf8;

INSERT INTO `class_type` (`id_class_type`, `name`) VALUES ('1', 'Практическое занятие');
INSERT INTO `class_type` (`id_class_type`, `name`) VALUES ('2', 'Лекция');
INSERT INTO `class_type` (`id_class_type`, `name`) VALUES ('3', 'Экзамен');
INSERT INTO `class_type` (`id_class_type`, `name`) VALUES ('4', 'Полувзвод практика');
INSERT INTO `class_type` (`id_class_type`, `name`) VALUES ('5', 'Зачёт');
INSERT INTO `class_type` (`id_class_type`, `name`) VALUES ('6', 'Консультация');
INSERT INTO `class_type` (`id_class_type`, `name`) VALUES ('7', 'Контрольная работа');
