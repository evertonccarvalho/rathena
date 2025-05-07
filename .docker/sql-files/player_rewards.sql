CREATE TABLE IF NOT EXISTS `player_rewards` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
    `account_id` INT UNSIGNED NOT NULL,
    `item_id` INT UNSIGNED NOT NULL,
    `quantity` SMALLINT UNSIGNED NOT NULL DEFAULT 1,
    `title` VARCHAR(100) NOT NULL,
    `description` VARCHAR(255) DEFAULT '',
    `delivered` TINYINT(1) NOT NULL DEFAULT 0,
    `created_at` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (`id`),
    INDEX (`account_id`),
    INDEX (`delivered`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
