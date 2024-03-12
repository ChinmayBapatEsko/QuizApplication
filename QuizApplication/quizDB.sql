-- MySQL dump 10.13  Distrib 8.0.36, for Win64 (x86_64)
--
-- Host: localhost    Database: quizapplication
-- ------------------------------------------------------
-- Server version	8.0.36

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `categories`
--

DROP TABLE IF EXISTS `categories`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `categories` (
  `category_id` varchar(10) NOT NULL,
  `category_name` varchar(255) NOT NULL,
  PRIMARY KEY (`category_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `categories`
--

LOCK TABLES `categories` WRITE;
/*!40000 ALTER TABLE `categories` DISABLE KEYS */;
INSERT INTO `categories` VALUES ('C_1','General Knowledge'),('C_2','Simple Math');
/*!40000 ALTER TABLE `categories` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `options`
--

DROP TABLE IF EXISTS `options`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `options` (
  `option_id` varchar(10) NOT NULL,
  `question_id` varchar(10) DEFAULT NULL,
  `option_text` text NOT NULL,
  `is_correct` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`option_id`),
  KEY `fk_option_question` (`question_id`),
  CONSTRAINT `fk_option_question` FOREIGN KEY (`question_id`) REFERENCES `questions` (`question_id`) ON DELETE CASCADE,
  CONSTRAINT `options_ibfk_1` FOREIGN KEY (`question_id`) REFERENCES `questions` (`question_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `options`
--

LOCK TABLES `options` WRITE;
/*!40000 ALTER TABLE `options` DISABLE KEYS */;
INSERT INTO `options` VALUES ('O_1','Qu_1','False',1),('O_10','Qu_5','True',0),('O_11','Qu_6','7',0),('O_12','Qu_6','8',1),('O_13','Qu_6','9',0),('O_14','Qu_6','10',0),('O_15','Qu_7','2',0),('O_16','Qu_7','3',0),('O_17','Qu_7','4',1),('O_18','Qu_7','5',0),('O_19','Qu_8','8',0),('O_2','Qu_1','True',0),('O_20','Qu_8','10',0),('O_21','Qu_8','12',1),('O_22','Qu_8','14',0),('O_23','Qu_9','3',0),('O_24','Qu_9','4',0),('O_25','Qu_9','5',0),('O_26','Qu_9','6',1),('O_27','Qu_10','13',1),('O_28','Qu_10','14',0),('O_29','Qu_10','15',0),('O_3','Qu_2','False',1),('O_30','Qu_10','16',0),('O_31','Qu_11','3',1),('O_32','Qu_11','4',0),('O_33','Qu_11','5',0),('O_34','Qu_11','6',1),('O_35','Qu_12','1',0),('O_36','Qu_12','2',1),('O_37','Qu_12','3',0),('O_38','Qu_12','4',0),('O_39','Qu_13','4',0),('O_4','Qu_2','True',0),('O_40','Qu_13','6',1),('O_41','Qu_13','8',0),('O_42','Qu_13','10',0),('O_43','Qu_14','2',0),('O_44','Qu_14','4',0),('O_45','Qu_14','6',1),('O_46','Qu_14','8',0),('O_47','Qu_15','13',0),('O_48','Qu_15','15',1),('O_49','Qu_15','17',0),('O_5','Qu_3','False',1),('O_50','Qu_15','19',0),('O_6','Qu_3','True',0),('O_7','Qu_4','False',0),('O_8','Qu_4','True',1),('O_9','Qu_5','False',1);
/*!40000 ALTER TABLE `options` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `questions`
--

DROP TABLE IF EXISTS `questions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `questions` (
  `question_id` varchar(10) NOT NULL,
  `quiz_id` varchar(10) DEFAULT NULL,
  `question_text` text NOT NULL,
  `question_type` varchar(2) NOT NULL,
  PRIMARY KEY (`question_id`),
  KEY `fk_question_quiz` (`quiz_id`),
  CONSTRAINT `fk_question_quiz` FOREIGN KEY (`quiz_id`) REFERENCES `quizzes` (`quiz_id`) ON DELETE CASCADE,
  CONSTRAINT `questions_ibfk_1` FOREIGN KEY (`quiz_id`) REFERENCES `quizzes` (`quiz_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `questions`
--

LOCK TABLES `questions` WRITE;
/*!40000 ALTER TABLE `questions` DISABLE KEYS */;
INSERT INTO `questions` VALUES ('Qu_1','Q_1','India is the largest country in the world.','TF'),('Qu_10','Q_2','What is 9 + 7?','SC'),('Qu_11','Q_3','What is the sum of 2 and 3?','MC'),('Qu_12','Q_3','What is the difference between 8 and 5?','MC'),('Qu_13','Q_3','What is the product of 4 and 2?','MC'),('Qu_14','Q_3','What is the result of 18 divided by 3?','MC'),('Qu_15','Q_3','What is the sum of 6 and 9?','MC'),('Qu_2','Q_1','The Taj Mahal is located in New Delhi.','TF'),('Qu_3','Q_1','Mahatma Gandhi was the first Prime Minister of India.','TF'),('Qu_4','Q_1','The national animal of India is the lion.','TF'),('Qu_5','Q_1','The capital of India is Mumbai.','TF'),('Qu_6','Q_2','What is 5 + 3?','SC'),('Qu_7','Q_2','What is 10 - 4?','SC'),('Qu_8','Q_2','What is 2 * 6?','SC'),('Qu_9','Q_2','What is 12 / 3?','SC');
/*!40000 ALTER TABLE `questions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `quizzes`
--

DROP TABLE IF EXISTS `quizzes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `quizzes` (
  `quiz_id` varchar(10) NOT NULL,
  `category_id` varchar(10) DEFAULT NULL,
  `quiz_title` varchar(255) NOT NULL,
  `quiz_description` text,
  PRIMARY KEY (`quiz_id`),
  KEY `fk_quiz_category` (`category_id`),
  CONSTRAINT `fk_quiz_category` FOREIGN KEY (`category_id`) REFERENCES `categories` (`category_id`) ON DELETE CASCADE,
  CONSTRAINT `quizzes_ibfk_1` FOREIGN KEY (`category_id`) REFERENCES `categories` (`category_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `quizzes`
--

LOCK TABLES `quizzes` WRITE;
/*!40000 ALTER TABLE `quizzes` DISABLE KEYS */;
INSERT INTO `quizzes` VALUES ('Q_1','C_1','India GK - True/False','Test your knowledge about India with these true/false questions.'),('Q_2','C_2','SolvewMe - Single Correct','Test your basic math skills with these single correct questions.'),('Q_3','C_2','SolvewMe - Multiple Choice','Test your basic math skills with these multiple-choice questions.');
/*!40000 ALTER TABLE `quizzes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `user` (
  `user_id` varchar(10) NOT NULL,
  `username` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `isAdmin` tinyint(1) DEFAULT NULL,
  `QuizAttempts` int DEFAULT NULL,
  `Accuracy` int DEFAULT NULL,
  PRIMARY KEY (`user_id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES ('U_1','abc','abc',0,33,44),('U_2','1','1',1,0,0),('U_3','abcd','abcd',0,0,0),('U_4','abcde','abcde',1,0,0);
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `useranswers`
--

DROP TABLE IF EXISTS `useranswers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `useranswers` (
  `user_answer_id` varchar(10) NOT NULL,
  `attempt_id` varchar(10) DEFAULT NULL,
  `question_id` varchar(10) DEFAULT NULL,
  `option_id` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`user_answer_id`),
  KEY `fk_useranswer_option` (`option_id`),
  KEY `fk_useranswer_question` (`question_id`),
  KEY `fk_useranswer_attempt` (`attempt_id`),
  CONSTRAINT `fk_useranswer_attempt` FOREIGN KEY (`attempt_id`) REFERENCES `userattempts` (`attempt_id`) ON DELETE CASCADE,
  CONSTRAINT `fk_useranswer_option` FOREIGN KEY (`option_id`) REFERENCES `options` (`option_id`) ON DELETE CASCADE,
  CONSTRAINT `fk_useranswer_question` FOREIGN KEY (`question_id`) REFERENCES `questions` (`question_id`) ON DELETE CASCADE,
  CONSTRAINT `useranswers_ibfk_1` FOREIGN KEY (`attempt_id`) REFERENCES `userattempts` (`attempt_id`),
  CONSTRAINT `useranswers_ibfk_2` FOREIGN KEY (`question_id`) REFERENCES `questions` (`question_id`),
  CONSTRAINT `useranswers_ibfk_3` FOREIGN KEY (`option_id`) REFERENCES `options` (`option_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `useranswers`
--

LOCK TABLES `useranswers` WRITE;
/*!40000 ALTER TABLE `useranswers` DISABLE KEYS */;
INSERT INTO `useranswers` VALUES ('UA_1','A_17','Qu_1','O_1'),('UA_10','A_18','Qu_5','O_9'),('UA_11','A_19','Qu_1','O_1'),('UA_12','A_19','Qu_2','O_3'),('UA_13','A_19','Qu_3','O_5'),('UA_14','A_19','Qu_4','O_7'),('UA_15','A_19','Qu_5','O_10'),('UA_16','A_20','Qu_10','O_30'),('UA_17','A_20','Qu_6','O_12'),('UA_18','A_20','Qu_7','O_18'),('UA_19','A_20','Qu_8','O_21'),('UA_2','A_17','Qu_2','O_3'),('UA_20','A_20','Qu_9','O_24'),('UA_21','A_21','Qu_10','O_28'),('UA_22','A_21','Qu_6','O_12'),('UA_23','A_21','Qu_7','O_16'),('UA_24','A_21','Qu_8','O_20'),('UA_25','A_21','Qu_9','O_24'),('UA_26','A_21','Qu_1','O_1'),('UA_27','A_21','Qu_2','O_3'),('UA_28','A_21','Qu_3','O_5'),('UA_29','A_21','Qu_4','O_7'),('UA_3','A_17','Qu_3','O_5'),('UA_30','A_21','Qu_5','O_10'),('UA_31','A_23','Qu_1','O_1'),('UA_32','A_25','Qu_1','O_1'),('UA_33','A_25','Qu_2','O_3'),('UA_34','A_25','Qu_3','O_5'),('UA_35','A_25','Qu_4','O_7'),('UA_36','A_25','Qu_5','O_10'),('UA_37','A_26','Qu_1','O_1'),('UA_38','A_26','Qu_2','O_3'),('UA_39','A_26','Qu_3','O_5'),('UA_4','A_17','Qu_4','O_7'),('UA_40','A_26','Qu_4','O_7'),('UA_41','A_26','Qu_5','O_10'),('UA_42','A_30','Qu_10','O_27'),('UA_43','A_30','Qu_6','O_11'),('UA_44','A_30','Qu_7','O_15'),('UA_45','A_30','Qu_8','O_19'),('UA_46','A_30','Qu_9','O_23'),('UA_47','A_33','Qu_1','O_1'),('UA_48','A_33','Qu_2','O_3'),('UA_49','A_33','Qu_3','O_5'),('UA_5','A_17','Qu_5','O_9'),('UA_50','A_33','Qu_4','O_7'),('UA_51','A_33','Qu_5','O_10'),('UA_52','A_34','Qu_1','O_2'),('UA_53','A_34','Qu_2','O_3'),('UA_54','A_34','Qu_3','O_5'),('UA_55','A_34','Qu_4','O_7'),('UA_56','A_34','Qu_5','O_10'),('UA_6','A_18','Qu_1','O_1'),('UA_7','A_18','Qu_2','O_3'),('UA_8','A_18','Qu_3','O_5'),('UA_9','A_18','Qu_4','O_7');
/*!40000 ALTER TABLE `useranswers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `userattempts`
--

DROP TABLE IF EXISTS `userattempts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `userattempts` (
  `attempt_id` varchar(10) NOT NULL,
  `user_id` varchar(10) DEFAULT NULL,
  `quiz_id` varchar(10) DEFAULT NULL,
  `Score` decimal(5,2) DEFAULT '0.00',
  PRIMARY KEY (`attempt_id`),
  KEY `fk_userattempt_quiz` (`quiz_id`),
  KEY `fk_userattempt_user` (`user_id`),
  CONSTRAINT `fk_userattempt_quiz` FOREIGN KEY (`quiz_id`) REFERENCES `quizzes` (`quiz_id`) ON DELETE CASCADE,
  CONSTRAINT `fk_userattempt_user` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`) ON DELETE CASCADE,
  CONSTRAINT `userattempts_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`),
  CONSTRAINT `userattempts_ibfk_2` FOREIGN KEY (`quiz_id`) REFERENCES `quizzes` (`quiz_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `userattempts`
--

LOCK TABLES `userattempts` WRITE;
/*!40000 ALTER TABLE `userattempts` DISABLE KEYS */;
INSERT INTO `userattempts` VALUES ('A_1','U_1','Q_2',0.00),('A_10','U_1','Q_1',0.00),('A_11','U_1','Q_1',0.00),('A_12','U_1','Q_1',0.00),('A_13','U_1','Q_1',0.00),('A_14','U_1','Q_1',0.00),('A_15','U_1','Q_1',0.00),('A_16','U_1','Q_1',0.00),('A_17','U_1','Q_1',0.00),('A_18','U_1','Q_1',0.00),('A_19','U_1','Q_1',0.00),('A_2','U_1','Q_1',0.00),('A_20','U_1','Q_2',40.00),('A_21','U_1','Q_1',60.00),('A_22','U_1','Q_1',0.00),('A_23','U_1','Q_1',0.00),('A_24','U_1','Q_1',0.00),('A_25','U_1','Q_1',60.00),('A_26','U_1','Q_1',60.00),('A_27','U_1','Q_1',0.00),('A_28','U_1','Q_1',0.00),('A_29','U_1','Q_3',0.00),('A_3','U_1','Q_1',0.00),('A_30','U_1','Q_2',20.00),('A_31','U_1','Q_3',0.00),('A_32','U_1','Q_1',0.00),('A_33','U_1','Q_1',60.00),('A_34','U_1','Q_1',40.00),('A_4','U_1','Q_3',0.00),('A_5','U_1','Q_1',0.00),('A_6','U_1','Q_1',0.00),('A_7','U_1','Q_2',0.00),('A_8','U_1','Q_1',0.00),('A_9','U_1','Q_3',0.00);
/*!40000 ALTER TABLE `userattempts` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-03-11 18:09:37
