-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema IoT
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema IoT
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `IoT` DEFAULT CHARACTER SET utf8 ;
USE `IoT` ;

-- -----------------------------------------------------
-- Table `IoT`.`Employee`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `IoT`.`Employee` ;

CREATE TABLE IF NOT EXISTS `IoT`.`Employee` (
  `employee_id` INT NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(255) NOT NULL,
  `surname` VARCHAR(255) NOT NULL,
  `email` VARCHAR(255) NOT NULL,
  `phone_number` INT NOT NULL,
  `password` VARCHAR(255) NULL,
  `rfid` VARCHAR(19) NOT NULL,
  PRIMARY KEY (`employee_id`),
  UNIQUE INDEX `employee_id_UNIQUE` (`employee_id` ASC) VISIBLE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `IoT`.`CheckIn`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `IoT`.`CheckIn` ;

CREATE TABLE IF NOT EXISTS `IoT`.`CheckIn` (
  `check_in_id` INT NOT NULL AUTO_INCREMENT,
  `checked_in` TINYINT NOT NULL,
  `date_time` DATETIME NOT NULL,
  `employee_id` INT NOT NULL,
  PRIMARY KEY (`check_in_id`, `employee_id`),
  UNIQUE INDEX `check_in_id_UNIQUE` (`check_in_id` ASC) VISIBLE,
  INDEX `fk_CheckIn_Employee_idx` (`employee_id` ASC) VISIBLE,
  CONSTRAINT `fk_CheckIn_Employee`
    FOREIGN KEY (`employee_id`)
    REFERENCES `IoT`.`Employee` (`employee_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
