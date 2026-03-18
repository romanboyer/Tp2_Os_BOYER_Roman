# TP2 - Polytech OS User : Protocole BEUIP

## Auteurs
BOYER Roman

## Avancement
- **Partie 1** : Datagrammes avec accusé de réception (Validée).
- **Partie 2** : Architecture client/serveur et identification (Validée).
- **Partie 3 (Bonus)** : Librairie `creme` et interpréteur de commandes (Validée).

## Structure du projet
- `servbeuip.c` : Serveur UDP implémentant le protocole BEUIP. Gère la table des utilisateurs et le routage des messages via des fonctions modulaires.
- `clibeuip.c` : Client de test permettant d'envoyer des commandes basiques au serveur local.
- `creme.c` / `creme.h` : Librairie (Commandes Rapides pour l'Envoi de Messages Evolués) encapsulant la gestion des processus (fork/kill) et la construction des datagrammes.
- `biceps.c` : Interpréteur de commandes interactif intégrant la librairie `creme` pour offrir une interface utilisateur fluide.
- `Makefile` : Fichier de construction. La compilation est configurée avec les flags `-Wall -Werror` pour garantir un code sûr.

## Utilisation
```bash
make
./biceps
