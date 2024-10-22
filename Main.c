#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRAINEES 100
#define MAX_TRAINERS 10
#define MAX_EQUIPMENT 20
#define MAX_WORKOUTS 50
#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 15
#define MAX_CONTACT_LENGTH 100

// Structure to store trainee details
typedef struct {
    char name[MAX_NAME_LENGTH];
    char contact[MAX_CONTACT_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char join_month[MAX_NAME_LENGTH];
    char payment_details[MAX_NAME_LENGTH];
    char workout_details[MAX_WORKOUTS][MAX_NAME_LENGTH]; // For storing workouts
    int workout_count;
    struct Trainer *trainer; // Pointer to assigned trainer
} Trainee;

// Structure to store trainer details
typedef struct {
    char name[MAX_NAME_LENGTH];
    char expertise[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    Trainee *trainees[MAX_TRAINEES]; // Array of pointers to trainees
    int trainee_count;
} Trainer;

// Structure to store equipment details
typedef struct {
    char name[MAX_NAME_LENGTH];
    char last_maintenance[MAX_NAME_LENGTH];
    char status[MAX_NAME_LENGTH];
} Equipment;

// Structure to manage the fitness studio
typedef struct {
    Trainee trainees[MAX_TRAINEES];
    Trainer trainers[MAX_TRAINERS];
    Equipment equipment[MAX_EQUIPMENT];
    int trainee_count;
    int trainer_count;
    int equipment_count;
} FitnessStudio;

// Function declarations
void add_trainee(FitnessStudio *studio, char *name, char *contact, char *phone, char *join_month, char *payment_details);
void add_trainer(FitnessStudio *studio, char *name, char *expertise, char *phone);
void add_equipment(FitnessStudio *studio, char *name, char *last_maintenance, char *status);
void assign_trainer_to_trainee(FitnessStudio *studio, char *trainee_name, char *trainer_name);
void update_workout_attendance(FitnessStudio *studio, char *trainee_name, char *workout);
void view_trainer_list(FitnessStudio *studio);
void view_trainee_details(FitnessStudio *studio, char *trainee_name);
void view_equipment_status(FitnessStudio *studio);
int available_slots(Trainer *trainer);

int main() {
    FitnessStudio studio = {0}; // Initialize studio

    // Add updated trainer names
    add_trainer(&studio, "Ramana", "Weightlifting", "1234567890");
    add_trainer(&studio, "Rakhi", "Yoga", "0987654321");
    add_trainer(&studio, "Koushik", "Cardio", "1112223333");
    add_trainer(&studio, "Praveen", "Zumba", "2223334444");
    add_trainer(&studio, "Vamsi", "CrossFit", "3334445555");
    add_trainer(&studio, "Rohit", "Pilates", "4445556666");

    // Add some sample trainees
    add_trainee(&studio, "Alice", "123 Street", "5555555555", "January", "Paid");
    add_trainee(&studio, "Bob", "456 Avenue", "6666666666", "February", "Pending");

    add_equipment(&studio, "Treadmill", "2024-01-15", "Good");
    add_equipment(&studio, "Dumbbells", "2024-02-10", "Under Maintenance");

    while (1) {
        printf("\n--- A2Z Fitness Studio Management ---\n");
        printf("1. View Trainers\n");
        printf("2. Assign Trainer to Trainee\n");
        printf("3. View Trainee Details\n");
        printf("4. Update Workout Attendance\n");
        printf("5. View Equipment Status\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        
        int choice;
        scanf("%d", &choice);
        getchar(); // Clear newline character from the buffer

        switch (choice) {
            case 1:
                view_trainer_list(&studio);
                break;
            case 2: {
                char trainee_name[MAX_NAME_LENGTH];
                char trainer_name[MAX_NAME_LENGTH];
                printf("Enter Trainee Name: ");
                fgets(trainee_name, MAX_NAME_LENGTH, stdin);
                trainee_name[strcspn(trainee_name, "\n")] = '\0'; // Remove newline

                printf("Enter Trainer Name: ");
                fgets(trainer_name, MAX_NAME_LENGTH, stdin);
                trainer_name[strcspn(trainer_name, "\n")] = '\0'; // Remove newline

                assign_trainer_to_trainee(&studio, trainee_name, trainer_name);
                break;
            }
            case 3: {
                char trainee_name[MAX_NAME_LENGTH];
                printf("Enter Trainee Name: ");
                fgets(trainee_name, MAX_NAME_LENGTH, stdin);
                trainee_name[strcspn(trainee_name, "\n")] = '\0'; // Remove newline

                view_trainee_details(&studio, trainee_name);
                break;
            }
            case 4: {
                char trainee_name[MAX_NAME_LENGTH];
                char workout[MAX_NAME_LENGTH];
                printf("Enter Trainee Name: ");
                fgets(trainee_name, MAX_NAME_LENGTH, stdin);
                trainee_name[strcspn(trainee_name, "\n")] = '\0'; // Remove newline

                printf("Enter Workout Details: ");
                fgets(workout, MAX_NAME_LENGTH, stdin);
                workout[strcspn(workout, "\n")] = '\0'; // Remove newline

                update_workout_attendance(&studio, trainee_name, workout);
                break;
            }
            case 5:
                view_equipment_status(&studio);
                break;
            case 6:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function implementations
void add_trainee(FitnessStudio *studio, char *name, char *contact, char *phone, char *join_month, char *payment_details) {
    if (studio->trainee_count < MAX_TRAINEES) {
        Trainee *trainee = &studio->trainees[studio->trainee_count++];
        strncpy(trainee->name, name, MAX_NAME_LENGTH);
        strncpy(trainee->contact, contact, MAX_CONTACT_LENGTH);
        strncpy(trainee->phone, phone, MAX_PHONE_LENGTH);
        strncpy(trainee->join_month, join_month, MAX_NAME_LENGTH);
        strncpy(trainee->payment_details, payment_details, MAX_NAME_LENGTH);
        trainee->workout_count = 0; // Initialize workout count
        trainee->trainer = NULL; // No trainer assigned initially
    } else {
        printf("Maximum trainees limit reached.\n");
    }
}

void add_trainer(FitnessStudio *studio, char *name, char *expertise, char *phone) {
    if (studio->trainer_count < MAX_TRAINERS) {
        Trainer *trainer = &studio->trainers[studio->trainer_count++];
        strncpy(trainer->name, name, MAX_NAME_LENGTH);
        strncpy(trainer->expertise, expertise, MAX_NAME_LENGTH);
        strncpy(trainer->phone, phone, MAX_PHONE_LENGTH);
        trainer->trainee_count = 0; // Initialize trainee count
    } else {
        printf("Maximum trainers limit reached.\n");
    }
}

void add_equipment(FitnessStudio *studio, char *name, char *last_maintenance, char *status) {
    if (studio->equipment_count < MAX_EQUIPMENT) {
        Equipment *equipment = &studio->equipment[studio->equipment_count++];
        strncpy(equipment->name, name, MAX_NAME_LENGTH);
        strncpy(equipment->last_maintenance, last_maintenance, MAX_NAME_LENGTH);
        strncpy(equipment->status, status, MAX_NAME_LENGTH);
    } else {
        printf("Maximum equipment limit reached.\n");
    }
}

void assign_trainer_to_trainee(FitnessStudio *studio, char *trainee_name, char *trainer_name) {
    Trainee *trainee = NULL;
    Trainer *trainer = NULL;

    // Find trainee
    for (int i = 0; i < studio->trainee_count; i++) {
        if (strcmp(studio->trainees[i].name, trainee_name) == 0) {
            trainee = &studio->trainees[i];
            break;
        }
    }

    // Find trainer
    for (int i = 0; i < studio->trainer_count; i++) {
        if (strcmp(studio->trainers[i].name, trainer_name) == 0) {
            trainer = &studio->trainers[i];
            break;
        }
    }

    // Assign trainer to trainee if available
    if (trainee && trainer) {
        if (available_slots(trainer) > 0) {
            trainee->trainer = trainer;
            trainer->trainees[trainer->trainee_count++] = trainee; // Add trainee to trainer's list
            printf("Trainer %s assigned to trainee %s.\n", trainer->name, trainee->name);
        } else {
            printf("Trainer %s already has 4 trainees.\n", trainer->name);
        }
    } else {
        printf("Invalid trainee or trainer name.\n");
    }
}

void update_workout_attendance(FitnessStudio *
