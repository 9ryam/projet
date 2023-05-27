#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/ioctl.h>

 
#define ANSI_COLOR_BLACK "\033[30m"
#define ANSI_COLOR_PINK "\033[35m"
#define ANSI_COLOR_GREEN "\033[32m"
#define ANSI_COLOR_YELW "\033[33m"
#define ANSI_COLOR_RED "\033[0;31m"
#define ANSI_COLOR_BLUE "\033[36m"
#define ANSI_FOND_WHITE "\033[47m"
#define ANSI_FOND_NOIR "\033[40m"
#define ANSI_FOND_ROSE "\033[45m"
#define ANSI_RESET "\033[0m" 
#define ANSI_SOULIGNER "\033[4m"
#define ANSI_GRAS "\033[1m"
#define MAX_LIVRES 50
#define MAX_ACHATS 3
#define MAX_NAME_LENGTH
#define TAILLE_MAX 120
int numCustomerConnecte = 0;

typedef struct {
    int reference;
    float price;
    char title[100];
    int quantities;
    char seize [10];
    char category[20];

} Book; //stucture livre

typedef struct {
    char lastname[50];
    char firstname[50];
    char email[100];
    int numCustomer;
} Customer;

typedef struct {
    float totalPanier;
    int reference;
    char titre[TAILLE_MAX];
} Achat;


Book books[MAX_LIVRES] = {
// MANGA
{31, 6.90, "ONE PIECE", 10, "grand", "MANGA"},
{32, 7.20, "BERSERK", 6, "moyen","MANGA"}, 
{33, 6.20, "NARUTO", 8, "petit", "MANGA"},
// BD
{21, 5.00, "LOU ", 8, "petit", "BD"},
{22, 4.70, "TINTIN" , 10, "grand", "BD"}, 
{23, 10.50, "ASTERIX" , 10, "moyen","BD"},
// LIVRE ENFANT
{10, 6.90, "PEANUTS", 6, "moyen","ENFANT"},
{11, 5.95, "T'CHOUPI", 6, "petit", "ENFANT"},
{12, 6.49, "LE PRTIT PRINCE", 6, "grand", "ENFANT"},
// FANTASTIQUE
{41, 9.30, "HARRY POTTER", 8, "petit", "FANTASTIQUE"},
{42, 8.99, "L'ETRANGE BLIOTHEQUE", 2, "moyen", "FANTASTIQUE"},
{43, 13.70, "RELENTLESS", 6, "grand", "FANTASTIQUE"},
// POLICIER
{26, 7.20, "ELEVATION", 8, "petit", "POLICIER"},
{27, 8.60, "LE PASSAGER SANS VISAGE", 6, "grand", "POLICIER"},
{28, 7.99, "MORT SUR LE NIL", 6, "moyen", "POLICIER"},
//SCIENCE FICTION
{60, 24.90, "DUNE", 6, "moyen", "SCIENCES-FI"},
{61, 5.30, "LA PLANETE DES SINGES", 6, "petit", "SCIENCES-FI"},
{62, 8.10, "FONDATION", 6, "grand", "SCIENCES-FI"},
// ROMANCE
{45, 8.90, "ORGEUIL ET PREJUGE", 10, "petit", "ROMANCE"},
{46, 7.90, "JAMAIS PLUS", 10, "moyen", "ROMANCE"},
{47, 15.86, "THE DEAL", 10, "grand", "ROMANCE"},
};




void centerText(const char* text) {
    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);

    int terminalWidth = ws.ws_col;
    int textLength = strlen(text);
    int padding = (terminalWidth - textLength) / 2;

    for (int i = 0; i < padding; i++) {
        printf(" ");
    }

    printf("%s\n", text);
}
void MainMenu(){
centerText("Bonjour, et bienvenu sur "ANSI_COLOR_PINK"CY SHOP BOOK\n"ANSI_RESET);
printf("Voulez vous utilisez notre site en mode gestion ou en mode achat ?\n"); 
  printf("[répondre par '1' pour gestion - '2' pour achat - '3' pour quitter : \n");
}
char* TitleByRef(int reference) {
    for (int i = 0; i < sizeof(books) / sizeof(books[0]); i++) {
        if (books[i].reference == reference) {
            return books[i].title;
        }
    }

    return "Titre inconnu";
}
void PurchaseMenu (){
  centerText("---- ⿴ MODE ACHAT ⿴ ----\n\n");
  printf("1] Rechercher un produit via son titre\n");
  printf("2] Acheter un produit\n");
  printf("3] Voir vos précédents achats\n");
  printf("4] Rechercher par catégorie\n");
  printf("5] Retour au menu principal\n");
  printf("Choisissez votre option via son numéro 1] 2] 3] 4] 5]\n\n");
  printf("→ ");
}
//mode achat
void ManagementMenu (){
  centerText("---- ⿴ MODE GESTION ⿴ ----\n\n");
  printf("1] Afficher les produits en bas stock\n");
  printf("2] Afficher les produits en rupture de stock\n");
  printf("3] Augmenter le stock\n");
  printf("4] Afficher la place restante en magasin\n");
  printf("5] Chercher le produit dans la base de données\n");
printf("6] Afficher la liste des livres\n");
  printf("7] Retour au menu principal\n");
  printf("Choisissez une option 1] 2] 3] 4] 5] 6] 7] :\n");
   printf("→ ");
}
//mode gestion
void LowStock() {
    FILE *file = fopen("livres.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    printf("\n===== PRODUITS EN BAS STOCK =====\n");

    int reference;
    float price;
    char title[100];
    int quantities;
    char taille[10];
    char category[50];

    while (fscanf(file, "Ref : %d - Prix : %.2f - Titre : %[^\n] - Stock :%d - Taille : %[^\n]", &reference, &price, title, &quantities, taille) == 5) {
        
            printf("Référence : %d\n", reference);
            printf("Titre : %s\n", title);
            printf("Quantité en stock : %d\n", quantities);
            printf("Catégorie : %s\n", category);
            printf("Prix : %.2f\n", price);
            printf("------------------------\n");
        
    }

    fclose(file);
}
// stock bas
void RemainingSpace(Book livres[], int nbLivre) {
    int totalSpace = 250;
    int usedSpace = 0;
    int i;
    for (i = 0; i < nbLivre; i++) {
        if (strcmp(livres[i].seize, "petit") == 0) {
            usedSpace += 1;
        } else if (strcmp(livres[i].seize, "moyen") == 0) {
            usedSpace += 2;
        } else if (strcmp(livres[i].seize, "grand") == 0) {
            usedSpace += 4;
        }
    }
    int remainingSpace = totalSpace - usedSpace;
    printf("Place restante en magasin : %d\n", remainingSpace);
}
//place restante en magasin
int GenerateNumber() {
    return rand() % 900000 + 100000; 
}
int hash(const char *str) {
    int hash = 0;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        hash = hash * 31 + str[i];
    }
 

    return abs(hash);
} // génération du numéro customer

void NewCustomerInformations( Customer *customer) {
    printf("Veuillez saisir votre nom : ");
    scanf("%s", customer->lastname);

    printf("Veuillez saisir votre prénom : ");
    scanf("%s", customer->firstname);

   

    char concat[200];
    sprintf(concat, "%s%s", customer->lastname, customer->firstname);
    customer->numCustomer = hash(concat);
    numCustomerConnecte = customer->numCustomer;
}
 // demander information au nouveau customer


int AskCustomerNumber() {
    int numCustomer;
    printf("Veuillez saisir votre numéro client : ");
     while (scanf("%d", &numCustomer) != 1) {
        printf("Numéro client invalide. Veuillez saisir un numéro valide : ");

        
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
    }
    return numCustomer;
}


int ResearchCustomer(const int numCustomer) {
    FILE *fichier = fopen("clients.txt", "r");
    if (fichier == NULL) {
        printf("Erreur.\n");
        return 0;
    }

    char ligne[200];
    while (fgets(ligne, sizeof(ligne), fichier)) {
        if (strstr(ligne, "Numéro client:")) {
            int numero;
            sscanf(ligne, "Numéro client: %d", &numero);
            if (numero == numCustomer) {
                fclose(fichier);
                return 1; 
            }
        }
    }

    fclose(fichier);
    return 0; 
}
// rechercher customer existant
void ConnectCustomer() {
  
    int numCustomer = AskCustomerNumber();
    if (ResearchCustomer(numCustomer)) {
       numCustomerConnecte = numCustomer;
        printf("\nConnecté avec succès !\n");
        printf("Bienvenue, client numéro : " ANSI_COLOR_YELW "%d\n\n\n"ANSI_RESET, numCustomer);
    } else {
        printf("Le numéro customer saisi n'existe pas. Veuillez réessayer.\n");
        ConnectCustomer(); 
    }
}
// connecter le customer existant
void DisplayBooksList() {
  centerText(ANSI_COLOR_PINK ANSI_SOULIGNER"⿻ CY SHOP BOOK ⿻\n\n" ANSI_RESET);
  
    printf("Voici la liste de titres des livres que nous avons :\n");
    printf(ANSI_COLOR_GREEN"𖣠"ANSI_RESET" MANGA "ANSI_COLOR_PINK"𖣠"ANSI_RESET" BD " ANSI_COLOR_BLUE"𖣠"ANSI_RESET " LIVRES ENFANTS " ANSI_COLOR_YELW"𖣠"ANSI_RESET " FANTASTIQUE " ANSI_COLOR_RED"𖣠"ANSI_RESET" POLICIER " ANSI_COLOR_BLACK"𖣠"ANSI_RESET" SCIENCES FICTION " "𖣠 ROMANCE\n\n" );
    
    
  printf("\n");
    // manga
        printf(ANSI_COLOR_BLACK "référence : 31 "
          ANSI_COLOR_GREEN"𖣠"ANSI_RESET " ONE PIECE • Eichiro ODA\t\
6€90\n\n");
        printf(ANSI_COLOR_BLACK "référence : 32 "
          ANSI_COLOR_GREEN"𖣠"ANSI_RESET " BERSERK • Kentaro MIURA\t\
7€20\n\n");
        printf(ANSI_COLOR_BLACK "référence : 33 "
          ANSI_COLOR_GREEN"𖣠"ANSI_RESET " NARUTO • Masashi KISHIMOTO\t\
6€20\n\n");
        
    // BD
        printf(ANSI_COLOR_BLACK "référence : 21 "
          ANSI_COLOR_PINK"𖣠"ANSI_RESET " LOU • Julien NEEL\t\
5€00\n\n");
        printf(ANSI_COLOR_BLACK "référence : 22 "
          ANSI_COLOR_PINK"𖣠"ANSI_RESET " TINTIN • HERGÉ\t\
4€70\n\n");
        printf(ANSI_COLOR_BLACK "référence : 23 "
          ANSI_COLOR_PINK"𖣠"ANSI_RESET " ASTERIX • Alain CHABAT\t\
10€50\n\n");
      
    // livre enfants
        printf(ANSI_COLOR_BLACK "référence : 10 "
          ANSI_COLOR_BLUE"𖣠"ANSI_RESET " PEANUTS • Charles SCHULZA\t\
6€90\n\n");
        printf(ANSI_COLOR_BLACK "référence : 11 "
          ANSI_COLOR_BLUE"𖣠"ANSI_RESET " T'CHOUPI • Thierry COURTIN\t\
6€49\n\n");
        printf(ANSI_COLOR_BLACK "référence : 12 " 
          ANSI_COLOR_BLUE"𖣠"ANSI_RESET " LE PETIT PRINCE • Antoine DE SAINT-EXUPERY\t\
6€49\n\n");

// fantastique
     printf(ANSI_COLOR_BLACK "référence : 41 "
          ANSI_COLOR_YELW"𖣠"ANSI_RESET " HARRY POTTER • J.K ROWLING\t\
9€30\n\n");
        printf(ANSI_COLOR_BLACK "référence : 42 "
          ANSI_COLOR_YELW"𖣠"ANSI_RESET " L'ETRANGE BIBLIOTHEQUE • Haruki MURAKAMI\t\
8€99\n\n");
        printf(ANSI_COLOR_BLACK "référence : 43 " 
          ANSI_COLOR_YELW"𖣠"ANSI_RESET " RELENTLESS • Karen LYNCH\t\
13€70\n\n");

// policier
     printf(ANSI_COLOR_BLACK "référence : 26 "
          ANSI_COLOR_RED"𖣠"ANSI_RESET " ELEVATION • Stephen KING\t\
7€20\n\n");
        printf(ANSI_COLOR_BLACK "référence : 27 "
          ANSI_COLOR_RED"𖣠"ANSI_RESET " LE PASSAGER SANS VISAGE • Nicolas BEUGLET\t\
8€60\n\n");
        printf(ANSI_COLOR_BLACK "référence : 28 " 
          ANSI_COLOR_RED"𖣠"ANSI_RESET " MORT SUR LE NIL • Agatha CHRISTIE\t\
7€99\n\n");


// science fiction
printf(ANSI_COLOR_BLACK "référence : 60 "
          ANSI_COLOR_BLACK"𖣠"ANSI_RESET " DUNE • Frank HERBERT\t\
10€00\n\n");
        printf(ANSI_COLOR_BLACK "référence : 61 "
          ANSI_COLOR_BLACK"𖣠"ANSI_RESET " LA PLANETE DES SINGES • Pierre BOULLE\t\
10€60\n\n");
        printf(ANSI_COLOR_BLACK "référence : 62 " 
          ANSI_COLOR_BLACK"𖣠"ANSI_RESET " FONDATION • Isaac ASIMOV\t\
8€66\n\n");

// romance
      printf(ANSI_COLOR_BLACK "référence : 45 "ANSI_RESET
          "𖣠" " ORGEUIL ET PREJUGE • Jean AUSTINE\t\
8€90\n\n");
        printf(ANSI_COLOR_BLACK "référence : 46 "ANSI_RESET
          "𖣠" " JAMAIS PLUS • Collenn HOOVER\t\
7€90\n\n");
        printf(ANSI_COLOR_BLACK "référence : 47 " ANSI_RESET
          "𖣠" " THE DEAL • Elle KENNEDY\t\
15€86\n\n");


    }
// affichage de la liste des livres

void wait(int seconds) {

    sleep(seconds *0,3); 

}
// attente de temps pour le system clear
void RefreshStock() {
    FILE* fichierLivre = fopen("livres.txt", "r+");
    if (fichierLivre == NULL) {
        printf("Erreur lors de l'ouverture du fichier \"livres.txt\".\n");
        return;
    }

    int references[MAX_LIVRES];
    int numBooks = 0;

    // Lire les références des livres sélectionnés
    for (int i = 0; i < numBooks; i++) {
        int reference = references[i];
        fseek(fichierLivre, 0, SEEK_SET);  // Retourner au début du fichier

        // Rechercher la référence dans le fichier et mettre à jour la quantité
        char ligne[256];
        while (fgets(ligne, sizeof(ligne), fichierLivre) != NULL) {
            int ref, quantite;
            float price;
            char titre[30];
            if (sscanf(ligne, "%d|%[^|]|%f|%d", &ref, titre, &price, &quantite) == 4 && ref == reference) {
                books[i].quantities -= quantite;  // Décrémenter la quantité disponible
                fseek(fichierLivre, -strlen(ligne), SEEK_CUR);  // Revenir à la ligne à mettre à jour
                fprintf(fichierLivre, "%d|%s|%.2f|%d\n", ref, titre, price, quantite);
                break;
            }
        }
    }

    fclose(fichierLivre);
}

// mise à jour du stock
void SearchByCategory(const char* category) {
    FILE* file = fopen("livres.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier livres.txt.\n");
        return;
    }

    Book book;
    char line[100];
    int found = 0;


    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Nom du livre :", 14) == 0) {
            sscanf(line, "Nom du livre : %[^\n]", book.title);
            fgets(line, sizeof(line), file);
            sscanf(line, "Numéro de référence : %d", &book.reference);
            fgets(line, sizeof(line), file);
            sscanf(line, "Catégorie : %[^\n]", book.category);
            fgets(line, sizeof(line), file);
            sscanf(line, "Quantité en stock : %d", &book.quantities);
            fgets(line, sizeof(line), file);
            sscanf(line, "Prix : %f", &book.price);
            fgets(line, sizeof(line), file);
            sscanf(line, "Taille : %[^\n]", book.seize);
          
char lowercaseCategory[50];
            int i;
            for (i = 0; book.category[i]; i++) {
                lowercaseCategory[i] = tolower(book.category[i]);
            }
            lowercaseCategory[i] = '\0';
            if (strcmp(book.category, category) == 0) {
                printf("Référence : %d\n", book.reference);
                printf("Titre : %s\n", book.title);
                printf("Quantité en stock : %d\n", book.quantities);
                printf("Prix : %.2f\n", book.price);
                printf("Taille : %s\n", book.seize);
                printf(ANSI_COLOR_RED ANSI_SOULIGNER"Catégorie : %s\n"ANSI_RESET, book.category);
                printf("\n");
              found = 1;
            }
        }
    }
if (!found) {
        printf("Aucun livre trouvé dans la catégorie '%s'.\n", category);
    }
    fclose(file);
} // rechercher un type de livre via catégorie

void SavePurchases(float totalPrix, int references[], int numBooks) {
  int numCustomer = numCustomerConnecte;
  int quantities = 0;
  char lastnameFichier [50];
    FILE *fichierCustomer;
    fichierCustomer = fopen("clients.txt", "a");

    if (fichierCustomer == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fprintf(fichierCustomer, "Numéro du client : %d\n", numCustomer);
    fprintf(fichierCustomer, "Total du panier : %.2f€\n", totalPrix);
    fprintf(fichierCustomer, "Livres sélectionnés :\n");

    for (int i = 0; i < numBooks; i++) {
        int reference = references[i];
      for (int j = 0; j < MAX_LIVRES; j++) {
       if (books[j].reference == reference) {
                books[j].quantities -= quantities; 
         FILE* fichierLivre = fopen("livres.txt", "r+");
                if (fichierLivre != NULL) {
                    fseek(fichierLivre, j * sizeof(Book), SEEK_SET);
                    fwrite(&books[j], sizeof(Book), 1, fichierLivre);
                    fclose(fichierLivre);
                } else {
                    printf("Erreur lors de l'ouverture du fichier \"livres.txt\".\n");
                } // Décrémenter la quantité disponible dans le stock global
                break;
            }
      }
        char *titre = TitleByRef(reference); 
        fprintf(fichierCustomer, "• Référence : %d • Titre : %s\n", reference, titre);
    }

    fclose(fichierCustomer); 
}
//sauvegarde les derniers achats
void DeleteCusotmersacc(int numCustomer) {
    FILE* fichierCustomer = fopen("clients.txt", "r");
    FILE* fichierTemp = fopen("temp.txt", "w");

    if (fichierCustomer == NULL || fichierTemp == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    int found = 0;
    char line[100];

    // Parcours du fichier customer
    while (fgets(line, sizeof(line), fichierCustomer)) {
        if (strncmp(line, "Numéro client: ", 15) == 0) {
            int customerNum;
            sscanf(line, "Numéro client: %d", &customerNum);

            if (customerNum == numCustomer) {
                found = 1;

                while (fgets(line, sizeof(line), fichierCustomer)) {
                    if (strcmp(line, "------------------------------------\n") == 0) {
                        break;
                    }
                }

                continue;  
            }
        }

        // Copier la ligne dans le fichier temporaire
        fprintf(fichierTemp, "%s", line);
    }

    fclose(fichierCustomer);
    fclose(fichierTemp);
    remove("clients.txt");
    rename("temp.txt", "clients.txt");

    if (found) {
        printf(ANSI_COLOR_YELW"\nLe compte clients a été supprimé avec succès, au plaisir de vous revoir.\n"ANSI_RESET);
      exit(0);
      
    } else {
        printf("Le customer n'a pas été trouvé dans le fichier.\n");
    }
}

void  AddPurchases() {
    Customer customer;
    Book livre;
    int references[MAX_LIVRES];
    int choix = 0;
    int numBooks = 0;
    float totalPrix = 0.0;
    int choixCustomer;
    int numCustomer = numCustomerConnecte;
    int quantite = 0;

    while (choix != -1 && numBooks < MAX_LIVRES) {
        int livreTrouve = 0; 

        printf("Sélectionnez un livre par son numéro de référence (ou -1 pour terminer votre panier) : \n");
        printf("➜ ");
        int result = scanf("%d", &choix);

        if (result != 1) {
            printf("Référence invalide. Veuillez entrer un numéro valide.\n");
           
            while (getchar() != '\n');
            continue;
        }

        if (choix == -1) {
            break;
        }

        for (int i = 0; i < MAX_LIVRES; i++) {
            if (books[i].reference == choix) {
                livreTrouve = 1;

                printf("Veuillez entrer la quantité souhaitée : ");
                result = scanf("%d", &quantite);
              

                if (result != 1) {
                    printf("Quantité invalide. Veuillez entrer un lastnamebre entier.\n");
                    // Vider le tampon d'entrée
                    while (getchar() != '\n');
                    continue;
                }

                if (quantite > books[i].quantities) {
                    printf("Quantité insuffisante. Veuillez réessayer.\n");
                    printf("1. Rester customer\n");
                    printf("2. Supprimer compte et derniers achats\n\n");
                    printf("Choisissez une option [1/2]: ");
                    scanf("%d", &choixCustomer);

                    if (choixCustomer == 2) {
                        DeleteCusotmersacc(numCustomer);  
                        return;  
                    } else {
                        livreTrouve = 0;
                        break;
                    }
                }

                references[numBooks] = choix;
                totalPrix += books[i].price * quantite;
                books[i].quantities -= quantite;  // Décrémente la quantité disponible
                numBooks++;
                printf("Livre ajouté au panier.\n");

                break;
            }
        }

    }

    printf(ANSI_COLOR_BLUE ANSI_SOULIGNER"\nTotal du panier : %.2f€\n"ANSI_RESET, totalPrix);

    char valider[4];
    printf("Souhaitez-vous valider votre panier ? [oui/non] : ");
    scanf("%3s", valider);
    printf("\n");

    if (strcmp(valider, "oui") == 0) {
        SavePurchases(totalPrix, references, numBooks);
        RefreshStock();
        centerText("-PANIER VALIDÉ-\n");
     
        centerText(ANSI_COLOR_YELW "Merci pour votre achat, au plaisir de vous revoir sur CY SHOP BOOK\n" ANSI_RESET);
    } else if (strcmp(valider, "non") == 0) {
        centerText("-PANIER ANNULÉ-\n");
        centerText(ANSI_COLOR_YELW "Aucun achat effectué... ;(" ANSI_RESET);
    } else {
        printf("Réponse invalide. Veuillez répondre par 'oui' ou 'non'.\n");
    }

    
} // panier customer

void SaveCustomer(const Customer *customer) {
   FILE* fichierCustomer = fopen("clients.txt", "a");
    if (fichierCustomer == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
 int estNouveauCustomer =0;
    if (!estNouveauCustomer) {
      fprintf(fichierCustomer, "- - -\n");
      fprintf(fichierCustomer, "Numéro customer: %d\n", customer->numCustomer);
      fprintf(fichierCustomer, "Nom: %s\n", customer->lastname);
      fprintf(fichierCustomer, "Prénom: %s\n", customer-> firstname);
        
        
    }
  else { 
  int totalPrix = 0;
  int references = 0;
  int numBooks = 0;
    
 SavePurchases(totalPrix, references, numBooks);
    fprintf(fichierCustomer, "- - -n\n");
  }
    fclose(fichierCustomer);
} // enregistre les nouveaux customers

void DisplayRecentsPurchases() {
    FILE* fichier = fopen("clients.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    int numCustomer = numCustomerConnecte;
    char ligne[200];
    char derniersAchats[3][200]; 
    int nbAchats = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (strstr(ligne, "Numéro du customer :") != NULL) {
            int numCustomer;
            sscanf(ligne, "Numéro du customer : %d", &numCustomer);
            if (numCustomer == numCustomer) {
                nbAchats = 0; 
            }
        } else if (strstr(ligne, "• Référence :") != NULL) {
            if (nbAchats < 3) {
                strcpy(derniersAchats[nbAchats], ligne);
                nbAchats++;
            } else {
                // Décaler les achats précédents vers le haut
                for (int i = 0; i < 2; i++) {
                    strcpy(derniersAchats[i], derniersAchats[i + 1]);
                }
                strcpy(derniersAchats[2], ligne);
            }
        }
    }

    fclose(fichier);

    printf("Derniers achats du customer %d :\n", numCustomer);
    if (nbAchats == 0) {
        printf("Aucun précédent achat.\n");
    } else {
        for (int i = 0; i < nbAchats; i++) {
            printf("%s", derniersAchats[i]);
        }
    }
} // dernier achat du customer X

  
void ReserchBookCustomer() {
    int nbLivre = 20;
    char searchTitle[200];
    
    do {
        printf("Entrez le titre du produit en majuscule : ");
        fgets(searchTitle, sizeof(searchTitle), stdin);
        searchTitle[strcspn(searchTitle, "\n")] = '\0';
        
        if (searchTitle[0] == '\0' || isdigit(searchTitle[0])) {
            printf("Titre invalide. Veuillez entrer un titre valide.\n");
            // Vider le tampon d'entrée
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
        } else {
            int produitTrouve = 0;
            
            for (int i = 0; i < nbLivre; i++) {
                if (strcmp(books[i].title, searchTitle) == 0) {
                    printf("Titre : %s\n", books[i].title);
                    printf("Référence : %d\n", books[i].reference);
                    printf("Prix : %.2f\n", books[i].price);
                    printf("Taille : %s\n", books[i].seize);
                    produitTrouve = 1;
                    break;
                }
            }
            
            if (!produitTrouve) {
                printf("Aucun produit correspondant trouvé.\n");
            }
        }
    } while (searchTitle[0] == '\0' || isdigit(searchTitle[0]));
}
// rechercher un livre du point de vu du customer

// mode gestion :

void SaveBooks(Book* books, int* numBooks, char category) {
    FILE* file = fopen("livres.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    
    for (int i = 0; i < *numBooks; i++) {
        if (books[i].reference != 0 || books[i].quantities != 0 || books[i].price != 0.0 || strlen(books[i].seize) > 0) {
            fprintf(file, "Nom du livre : %s\n", books[i].title);
            fprintf(file, "Numéro de référence : %d\n", books[i].reference);
            fprintf(file, "Catégorie : %s\n", books[i].category);
            fprintf(file, "Quantité en stock : %d\n", books[i].quantities);
            fprintf(file, "Prix : %.2f\n", books[i].price);
            fprintf(file, "Taille : %s\n", books[i].seize);
            fprintf(file, "\n");
        }
    }
    
    fclose(file);
} // enregistre les livres dans le fichier livre

void OutofStock() {
    
    for (int i = 0; i <21; i++) {
        if (books[i].quantities == 0) {
          printf("Livres qui sont en rupture de stock :\n");
          printf("Livre : %s\n", books[i].title);
          printf("Référence : %d\n", books[i].reference);
          printf("Catégorie : %s\n", books[i].category);
          printf("Quantité en stock : %d\n", books[i].quantities);
            
        }
    } 
      printf("Aucun livre est en rupture de stock\n");
} // rupture de stock


void searchProductByReference(Book books[], int nbBook, int reference) {
    int i;
    for (i = 0; i < nbBook; i++) {
        if (books[i].reference == reference) {
            printf("Référence : %d\n", books[i].reference);
            printf("Titre : %s\n", books[i].title);
            printf("Catégorie : %s\n", books[i].category);
            printf("Quantité en stock : %d\n", books[i].quantities);
            printf("Prix : %.2f\n", books[i].price);
            printf("Taille : %s\n", books[i].seize);
            return;
        }
    }
    printf("Produit non trouvé.\n");
} // cherche livre avec la référence



void ShowRemainingSpace(Book* books, int totalBooks) {
  int totalSpace = 500; 
  int totalOccupiedSpace = 0;
  
  for (int i = 0; i < MAX_LIVRES; i++) {
    if (strcmp(books[i].seize, "petit") == 0) {
      totalOccupiedSpace += books[i].quantities * 1;
    } 
    else if (strcmp(books[i].seize, "moyen") == 0) {
      totalOccupiedSpace += books[i].quantities * 2;
    } 
    else if (strcmp(books[i].seize, "grand") == 0) {
      totalOccupiedSpace += books[i].quantities * 4;
    }
  }
   
  int remainingSpace = totalSpace - totalOccupiedSpace;
  
  printf("Place restante du magasin : %d\n", remainingSpace);
} // montre la place restante dans le magasin



  int getBookSize(Book book) {
    if (strcmp(book.seize, "petite") == 0) {
        return 1;
    } else if (strcmp(book.seize, "moyen") == 0) {
        return 2;
    } else if (strcmp(book.seize, "grand") == 0) {
        return 4;
    }
    
    // Valeur par défaut si la taille n'est pas valide
    return 0;
}
  //Trouve la place d'un livre en fonction de sa taille 
  
void IncreaseStockByReference(int reference, int quantities) {
    int bookIndex = -1;
    int bookSize = 0;

    // Recherche du livre et récupération de sa taille
    for (int i = 0; i < MAX_LIVRES; i++) {
        if (books[i].reference == reference) {
            bookIndex = i;
            bookSize = getBookSize(books[i]);
            break;
        }
    }

    // Vérification du livre trouvé et de la disponibilité de l'espace dans le magasin
    if (bookIndex != -1) {
        int totalOccupiedSpace = 0;

        // Calcul de l'espace déjà occupé par les livres
        for (int i = 0; i < MAX_LIVRES; i++) {
            if (i != bookIndex) {
                totalOccupiedSpace += getBookSize(books[i]) * books[i].quantities;
            }
        }

        int remainingSpace = 500 - totalOccupiedSpace;

        // Vérification de la disponibilité de l'espace pour les nouvelles quantités
        if (remainingSpace >= quantities * bookSize) {
            books[bookIndex].quantities += quantities;
            printf("Stock du livre '%s' augmenté de %d.\n", books[bookIndex].title, quantities);
            printf("Nouveau stock : %d.\n", books[bookIndex].quantities);
        } else {
            printf("Espace insuffisant dans le magasin pour augmenter le stock du livre '%s'.\n", books[bookIndex].title);
            printf("Place restante dans le magasin : %d.\n", remainingSpace);
        }
    } else {
        printf("Aucun livre trouvé avec cette référence.\n");
    }
}

 // augmente le stock avec la reference



void ShowLowStock() {
  printf("Livres avec un stock inférieur ou égal à 5 :\n");

    for (int i = 0; i < 21; i++) {
     
        if (books[i].quantities <= 5) {
          printf("Livre : %s\n", books[i].title);
          printf("Référence : %d\n", books[i].reference);
          printf("Catégorie : %s\n", books[i].category);
          printf("Quantité en stock : %d\n", books[i].quantities);
              
       }   
    } 
  
} // stock bas


void FindBookByTitle(const char* title) {
    for (int i = 0; i < MAX_LIVRES; i++) {
        if (strstr(books[i].title, title) != NULL) {
            printf("Livre trouvé : %s\n", books[i].title);
            printf("Référence : %d\n", books[i].reference);
            printf("Quantité en stock : %d\n", books[i].quantities);
            printf("Catégorie : %s\n", books[i].category);
            printf("Prix : %.2f\n", books[i].price);
            printf("Taille : %s\n", books[i].seize);
            return;
        }
    }
    printf("Aucun livre trouvé avec ce titre.\n");
} // trouver le livre avec la titre

void FindBookByReference(int reference) {
    for (int i = 0; i < MAX_LIVRES; i++) {
        if (books[i].reference == reference) {
          printf("Livre trouvé : %s\n", books[i].title);
          printf("Référence : %d\n", books[i].reference);
          printf("Catégorie : %s\n", books[i].category);
          printf("Quantité en stock : %d\n", books[i].quantities);
          printf("Prix : %.2f\n", books[i].price);
          printf("Taille : %s\n", books[i].seize);
          return;
        }
    }
    printf("Aucun livre trouvé avec cette référence.\n");
} // trouve livre avec la reference
  
int readIntInput() {
    char input[50];
    fgets(input, sizeof(input), stdin);

    int value;
    if (sscanf(input, "%d", &value) != 1) {
        printf("Entrée invalide. Veuillez entrer un nombre.\n");
    }

    return value;
}
////////////////////////////////////////////////////////////
int main() {  
int estNouveauCustomer = 0;
int nbBook = 20;
Customer customer;
char rep[4];
int mode = 0;
int choice = 0;
int referencebook = 0;
int quantities = 0;
int reference = 0;
char input[10];
int i;
int optiong;
int option;
char title[30];
char category[50];
int numBooks;
int GoodAnswer = 0;
int totalBooks = 0;
  
  while (mode != 3) {
    do {
       MainMenu
        ();
        scanf("%s", input);
        getchar();
        int i;
        for (i = 0; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                printf("Option invalide. Veuillez entrer un numéro valide.\n");
                break;
            }
        }

        if (input[i] == '\0') {
            mode = atoi(input);

            if (mode < 1 || mode > 3) {
                printf("Option invalide. Veuillez entrer un numéro valide.\n");
            }
        }
    } while (mode < 1 || mode > 3);

    switch (mode) {
        case 1: // mode gestion
            while (1) {
                do {
                    ManagementMenu();
                    scanf("%s", input);
                    getchar();
                    int i;
                    for (i = 0; input[i] != '\0'; i++) {
                        if (!isdigit(input[i])) {
                            printf("Option invalide. Veuillez entrer un numéro valide.\n");
                            break;
                        }
                    }

                    if (input[i] == '\0') {                       
                        optiong = atoi(input);
                        if (optiong < 1 || optiong > 7) {
                            printf("Option invalide. Veuillez entrer un numéro valide.\n");
                        }
                    }
                } while (optiong < 1 || optiong > 7);

                switch (optiong) {
                    case 1:
                        ShowLowStock();
                        break;
                    case 2:
                        OutofStock();
                        break;
                    case 3:
                        printf("Entrez la référence du produit : ");
                        scanf("%d", &reference);
                        printf("Entrez la quantity à ajouter : ");
                        scanf("%d", &quantities);
                        IncreaseStockByReference(reference, quantities);
                        break;
                    case 4:
                        ShowRemainingSpace(books, totalBooks);
                        break;
                    case 5:
                       printf("Voulez-vous rechercher un livre par son titre ou par sa référence ? [1/2]\n");
printf("1. Titre\n");
printf("2. Référence\n");
printf("Choisissez : ");

int choice = readIntInput();

while (choice != 1 && choice != 2) {
    printf("Choisissez entre le titre ou la référence :\n");
    choice = readIntInput();
}

if (choice == 1) {
    printf("Veuillez entrer le titre du livre :\n");
    char namebook[50];
    scanf("%s", namebook);
    FindBookByTitle(namebook);
} else if (choice == 2) {
    printf("Veuillez entrer la référence du produit :\n");
    int referencebook = readIntInput();
    FindBookByReference(referencebook);
}
                        break;
                    case 6:
                        DisplayBooksList();
                        break;
                    case 7:
                         system("clear");
                        break;
                }

                if (optiong == 7) {
                   
                    break;
                }
            }
            break;
        case 2: // mode achat                        
            
           while (!GoodAnswer) {
        printf("Avez-vous un compte client ? [oui/non] : ");
        scanf("%3s", rep);

        if (strcmp(rep, "non") == 0) {
            estNouveauCustomer = 1;
            GoodAnswer = 1;
        } else if (strcmp(rep, "oui") == 0) {
            estNouveauCustomer = 0;
            GoodAnswer = 1;
        } else {
            printf("Réponse invalide. Veuillez répondre par 'oui' ou 'non'.\n");
        }
             if (estNouveauCustomer) {
        NewCustomerInformations(&customer);
        SaveCustomer(&customer);
     
        printf("\nBienvenue ! Voici vos informations :\n");
        printf("Nom : %s\n", customer.lastname);
        printf("Prénom : %s\n", customer.firstname);
        printf("Numéro client : %d\n", customer.numCustomer);
    } else {
      ConnectCustomer();
        }
  if (getchar() != '\n');
  
  centerText(ANSI_FOND_NOIR ANSI_COLOR_YELW "- Appuyer sur Entrée -" ANSI_RESET);
    
while (getchar() != '\n');
    system("clear");
            while (1) {
    PurchaseMenu();
    scanf("%9s", input);
    getchar();

    int option = atoi(input);

    if (option < 1 || option > 5) {
        printf("Option invalide. Veuillez entrer un numéro valide.\n");
        continue;  
    }
                switch (option) {
                    case 1:
                      printf("Entré le titre du livre en majuscules : ");
                        scanf("%s", title);
                       FindBookByTitle(title);
                        break;
                    case 2:
                        DisplayBooksList();
                        AddPurchases();
                        break;
                    case 3:
                        DisplayRecentsPurchases();
                        break;
                  case 4:
                    printf("Entrez la catégorie de livres en majuscules : ");
                    scanf("%s", category);
                   SearchByCategory(category);
                  
                    case 5:
                       
                        break;
                }

                if (option == 5) {
                    system("clear");
                    break;
                }
            }

            break;
        case 3:
            // Quitter l'application
            return 0;
    }
}
  } 
return 0; }
