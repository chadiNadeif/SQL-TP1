CREATE TABLE IF NOT EXISTS LIEUX (
    LieuxID INT PRIMARY KEY,
    LieuxName TEXT,
    LieuxDescript TEXT
);
CREATE TABLE IF NOT EXISTS OBJECTS (
    ObjectsID INT PRIMARY KEY,
    ObjectsName TEXT,
    ObjectsDescript TEXT,
    LieuxObjects INT,
    FOREIGN KEY (LieuxObjects) REFERENCES LIEUX(LieuxID)
);
CREATE TABLE IF NOT EXISTS PLAYERS (
    JoueursID INT PRIMARY KEY,
    JoueursName TEXT,
    JoueursVie INT,
    JoueursForce INT,
    LieuxJoueur INT,
    FOREIGN KEY (LieuxJoueur) REFERENCES LIEUX(LieuxID)
);
CREATE TABLE IF NOT EXISTS PNJ (
    PNJID INT PRIMARY KEY,
    PNJName TEXT,
    PNJDescript TEXT,
    PNJDialogue TEXT,
    LieuxPNJ INT,
    FOREIGN KEY (LieuxPNJ) REFERENCES LIEUX(LieuxID)
);
CREATE TABLE IF NOT EXISTS ENNEMIS(
    EnnemisID INT PRIMARY KEY,
    EnnemisName TEXT,
    EnnemisVie INT,
    EnnemisForce INT,
    LieuxEnnemis INT,
    FOREIGN KEY (LieuxEnnemis) REFERENCES LIEUX(LieuxID)
);
CREATE TABLE IF NOT EXISTS INVENTAIRE(
    InventaireID INT PRIMARY KEY,
    PlayerID INT,
    ItemsID INT,
    FOREIGN KEY (PlayerID) REFERENCES PLAYERS(JoueursID),
    FOREIGN KEY (ItemsID) REFERENCES OBJECTS(ObjectsID)
);
CREATE TABLE IF NOT EXISTS QUETES(
    QuetesID INT PRIMARY KEY,
    QuetesDescript TEXT,
    QuetesComplete BOOLEAN,
    PlayerID INT,
    NPCID INT,
    FOREIGN KEY (PlayerID) REFERENCES PLAYERS(JoueursID),
    FOREIGN KEY (NPCID) REFERENCES PNJ(PNJID)
);
CREATE TABLE IF NOT EXISTS PNJ_QUETES(
    PNJ_QuestsID INT PRIMARY KEY,
    NPCID INT,
    QuetesID INT,
    FOREIGN KEY (NPCID) REFERENCES PNJ(PNJID),
    FOREIGN KEY (QuetesID) REFERENCES QUETES(QuetesID)
);
INSERT INTO LIEUX (LieuxID,LieuxName,LieuxDescript)
VALUES
(1,'village','un village avec peu d habitant qui se trouve a cote dune foret tu peux trouver une epee et des fleurs'),
(2,'foret','une foret avec un brouillard si intense qu il est impossibe de voire plus de 30cm une torche se trouve ici mais aussi des goblibns et des loup'),
(3,'grotte','une grotte cacher grace a un sortilège avec une mana trés intance plein ennemie qui se trouve a l interieur et un fouet modie'),
(4,'Realm of the death','un endroit ou tout les ames des aventurier qui ont perdu leur vie dans la grotte');
INSERT INTO OBJECTS (ObjectsID,ObjectsName,ObjectsDescript,LieuxObjects)
VALUES
(5,'Aranara torche','une torche avec une flame incruster de mana qui permet de voir meme a travertle brouillard',2),
(6,'Sword','une epee ordinaire mais tres tranchante',1),
(7,'fouet','un fouet d apparence ordinaire mais qui possede une energie modite capable de tuer les creatures qui ne possede pas de corps +2 force',3),
(8,'Potion de vie','une potion qui permet de restorer des point de vie',1),
(9,'The king dagger','la dague avec la quelle l abomination a ete tuer',4),
(10,'fleur','des fleurs tres rare utiliser pour creer des potion',1);
INSERT INTO ENNEMIS (EnnemisID,EnnemisName,EnnemisVie,EnnemisForce,LieuxEnnemis)
VALUES
(10,'loup',3,5,2),
(11,'goblin',2,7,2),
(12,'phantom',7,9,3),
(13,'squelette',5,15,3),
(14,'abomination',20,20,4);
