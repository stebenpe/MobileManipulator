# Omron LD-90
De LD-90 heeft een ingescande kaart van de elektrotechniek gang (van G2 tot en met H2). Hier kan de LD-90 autonoom in rondreiden als deze een punt door krijgt waar deze heen moet. De aansturing waar en wanneer de LD-90 ergens heen moet gaat via ROS2. De communicatie hiertussen gaat bedraad via de router met he ARCL protocol. De instellingen hiervan zijn als volgt:


## Handleiding
Het setup LD-90.docx is een handleiding voor het gebruiken van de Omron LD-90. Dit is een verkorte samenvatting van de grote handleiding en met de inloggegevens en instellingen hoe de LD-90 nu is ingesteld.

## Zei lidar's instellen
Omdat er een frame en robot arm bovenop de LD-90 komt is deze te hoog om onder een tafel door te gaan. En omdat de standaard lidar die er op zit alleen horizontaal kijkt op een laag niveau kan deze tafelbladen niet zien en er dus tegenaan rijden. Daarom zijn er 2 zei lidars toegevoegd. Deze kijken links en rechts van de robot verticaal. Let er wel op dat bij het inscannen van een map hij deze lidars niet meeneemt met het genereren van de map. Hierdoor denkt de LD-90 soms dat hij onder een tafel door kan gaan maar als hij er is zien de zei lidars de tafel. Om dit te voorkomen is het wel van belang om de kaart aan te passen met verboden gebieden waar de tafels en ander positiefe en negatieve objecten zijn.

De instellingen van de zei lidar's instellen is als volgt.

Lidar 1(rechts): 
```
X: -76, Y: -250, Z: 530
```
Lidar 2(links):
```
X: -76, Y: 250, Z: 530
```

## Voeding