CREATE DATABASE  IF NOT EXISTS `angadi` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `angadi`;
-- MySQL dump 10.13  Distrib 5.5.34, for debian-linux-gnu (i686)
--
-- Host: 192.168.1.102    Database: angadi
-- ------------------------------------------------------
-- Server version	5.5.34-0ubuntu0.13.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `bill`
--

DROP TABLE IF EXISTS `bill`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bill` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `date` datetime NOT NULL,
  `customer_id` int(11) DEFAULT NULL,
  `actualAmount` double NOT NULL DEFAULT '0',
  `discount` double NOT NULL DEFAULT '0',
  `totalAmount` double NOT NULL DEFAULT '0',
  `dueAmount` double NOT NULL DEFAULT '0',
  `paidStatus` enum('P','U') NOT NULL COMMENT 'P => Paid; U => Unpaid',
  `status` enum('A','I','D') NOT NULL DEFAULT 'A' COMMENT 'A => Active; I => Inactive; D => Deleted',
  `createdDate` datetime DEFAULT NULL,
  `modifiedDate` datetime DEFAULT NULL,
  `modifiedBy` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bill`
--

LOCK TABLES `bill` WRITE;
/*!40000 ALTER TABLE `bill` DISABLE KEYS */;
/*!40000 ALTER TABLE `bill` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `bill_item`
--

DROP TABLE IF EXISTS `bill_item`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bill_item` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `bill_id` int(11) NOT NULL,
  `product_id` int(11) NOT NULL,
  `unitPrice` double NOT NULL DEFAULT '0',
  `quantity` double NOT NULL DEFAULT '0',
  `total` double NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bill_item`
--

LOCK TABLES `bill_item` WRITE;
/*!40000 ALTER TABLE `bill_item` DISABLE KEYS */;
/*!40000 ALTER TABLE `bill_item` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `categories`
--

DROP TABLE IF EXISTS `categories`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `categories` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `code` varchar(100) NOT NULL,
  `name` varchar(200) NOT NULL,
  `status` enum('A','I','D') NOT NULL DEFAULT 'A' COMMENT 'A => Active; I => Inactive; D => Delete',
  `createdDate` datetime DEFAULT NULL,
  `modifiedDate` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `categories`
--

LOCK TABLES `categories` WRITE;
/*!40000 ALTER TABLE `categories` DISABLE KEYS */;
INSERT INTO `categories` VALUES (1,'1','Kalar','A','2014-04-30 19:26:39','2014-05-05 16:11:22'),(2,'2','Vijay','D','2014-04-30 19:26:56','2014-05-03 19:33:24'),(3,'3','Paruppu','A','2014-04-30 19:27:15','2014-05-05 16:11:04'),(4,'4','Test 4','D','2014-04-30 19:27:29','2014-05-03 15:18:45'),(5,'5','Category 55','D','2014-05-03 11:38:31','2014-05-03 15:18:27'),(6,'2','Arisi','A','2014-05-05 16:10:52',NULL);
/*!40000 ALTER TABLE `categories` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `customers`
--

DROP TABLE IF EXISTS `customers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `customers` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `code` varchar(100) NOT NULL,
  `name` varchar(200) NOT NULL,
  `type` varchar(45) NOT NULL,
  `creditLimit` double NOT NULL,
  `contactPerson` varchar(200) DEFAULT NULL,
  `address1` varchar(255) DEFAULT NULL,
  `address2` varchar(255) DEFAULT NULL,
  `city` varchar(100) DEFAULT NULL,
  `state` varchar(100) DEFAULT NULL,
  `country` varchar(100) DEFAULT NULL,
  `pincode` varchar(10) DEFAULT NULL,
  `phone1` varchar(20) DEFAULT NULL,
  `phone2` varchar(20) DEFAULT NULL,
  `mobile1` varchar(20) DEFAULT NULL,
  `mobile2` varchar(20) DEFAULT NULL,
  `email` varchar(80) DEFAULT NULL,
  `website` varchar(80) DEFAULT NULL,
  `notes` text,
  `status` enum('A','I','D') NOT NULL DEFAULT 'A',
  `createdDate` datetime DEFAULT NULL,
  `modifiedDate` varchar(45) DEFAULT NULL,
  `modifiedBy` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customers`
--

LOCK TABLES `customers` WRITE;
/*!40000 ALTER TABLE `customers` DISABLE KEYS */;
INSERT INTO `customers` VALUES (1,'1','test','Retailer',1000,'Selvam','1/8 Main road','address 2','Thonugal','Tamil nadu','India','626 104','9789571686','9994496434','9789571686','9994496434','jpselvam@rocketmail.com','www.test.com','<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:\'Sans Serif\'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">This is test note</p></body></html>','D','2014-04-26 12:13:52','2014-05-03 12:27:23',NULL),(2,'2','Selvam','Whole Saler',2000,'Selvam','','','','','','','','','','','','','<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:\'Sans Serif\'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>','D','2014-04-28 10:35:06','2014-05-03 14:32:51',NULL);
/*!40000 ALTER TABLE `customers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `products`
--

DROP TABLE IF EXISTS `products`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `products` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `code` varchar(100) NOT NULL,
  `name` varchar(200) NOT NULL,
  `unit` varchar(100) NOT NULL,
  `category_id` int(11) NOT NULL,
  `mrp` double NOT NULL,
  `sprice` double NOT NULL,
  `wholeSalePrice` double NOT NULL,
  `status` enum('A','I','D') NOT NULL DEFAULT 'A' COMMENT 'A => Active; I => Inactive; D => Deleted',
  `createdDate` datetime DEFAULT NULL,
  `modifiedDate` datetime DEFAULT NULL,
  `modifiedBy` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `products`
--

LOCK TABLES `products` WRITE;
/*!40000 ALTER TABLE `products` DISABLE KEYS */;
INSERT INTO `products` VALUES (1,'1','Ponni','Kgs',6,50,45,42,'A','2014-04-28 18:57:48',NULL,NULL);
/*!40000 ALTER TABLE `products` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transactions`
--

DROP TABLE IF EXISTS `transactions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `transactions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `bill_id` int(11) NOT NULL,
  `paidAmount` double NOT NULL DEFAULT '0',
  `paidOn` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `paidBy` varchar(150) DEFAULT NULL,
  `mode` varchar(45) NOT NULL,
  `status` enum('A','I','D') NOT NULL DEFAULT 'A' COMMENT 'A => Active; I => Inactive; D => Deleted',
  `createdDate` datetime DEFAULT NULL,
  `modifiedDate` datetime DEFAULT NULL,
  `modifiedBy` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transactions`
--

LOCK TABLES `transactions` WRITE;
/*!40000 ALTER TABLE `transactions` DISABLE KEYS */;
/*!40000 ALTER TABLE `transactions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(100) NOT NULL,
  `password` varchar(60) NOT NULL,
  `createdDate` datetime DEFAULT NULL,
  `modifiedDate` datetime DEFAULT NULL,
  `modifiedBy` int(11) DEFAULT '0',
  `status` enum('A','I','D','N') NOT NULL DEFAULT 'N',
  `rememberMe` enum('Y','N') DEFAULT 'N',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'admin','098f6bcd4621d373cade4e832627b4f6',NULL,NULL,0,'A','N');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-05-05 18:34:48
