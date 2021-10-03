#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;


//below is the basic infrastructure for a backward and forward chaining program, I originally coded this with forward chaining in mind so we may have to make some modifications for backward
//chaining but they shouldn't be major.

/* Defining a structure for facts, this structure will contain a flag value representing
the facts status in the program (-1 for not known, 0 for no, 1 for yes.)
It will also contain a string value for the related question (if relevant)*/
struct fact
{
    int status = -1;
    string name = "null";
    string question = "null";

};

const int VARLITSIZE = 31;
fact varlt[VARLITSIZE]; //As was in the example, we have a variable list. This time of course is a 2d array of the "fact" structure we've created.
const int CLVARLITSIZE = 120;
fact* clvarlt[CLVARLITSIZE]; // This is the corresponding clause variable list, it will contain pointers to our variable list, as they will be reused throughout the clause variable list.
char contin = 'Y';
stack<string> backChainConclusions; //This is the backward chaining conclusion stack, any string representing a disease added to it means the patient has the disease.
int backClauseNum; //index of clause number for backwards chaining
int result; //int value for result of questions/status of symptom.
string dName; //name of disease to be retrieved once we have a conclusion from the backward chain
string* forwardClVarLt[4]; //clause variable list for forward chain.
queue<string> forwardConclusions;

void initialize();
int askQuestion(fact& input);

int main()
{
    while(contin == 'y'||contin == 'Y'){
    initialize();

    //This next section will be our rule base of our knowledge base.
    //we have 8 diseases to diagnose, so we will run a loop 8 times, once to check each disease.
    bool diagnosed = false; //Flag value for whether the disease has been found.
    int i = 1; //counter
    while(i <= 8 && diagnosed == false){
        //will check each disease according to what the value of the i counter is.
        //We have 30 rules total (may end up with more) so they will be divided among these 8 cases.
        switch(i){
            case 1:{
            cout << "Checking Pulmonary Stenosis." << endl;
                /*According to the formula:
                CLAUSE NUMBER = 4* (RULE NUMBER  / 10 - 1) + 1
                We will be dividing up our clause variable list

                CLAUSE NUMBER = 4* (RULE NUMBER  / 10 - 1)
                this formula will be to find the index in the clvarlt array (because arrays are base 0)
                */

            //************************
            /*rule 10*/
            //************************
            backClauseNum = 4* (10 / 10 - 1);
                        //rule num^
            //ask question for murmur
            result = askQuestion(*clvarlt[backClauseNum]); //returns whether the symptom is present or not
                //if true, ask question for Irregular heartbeat
                if(result == 1){
                    result = askQuestion(*clvarlt[backClauseNum + 1]);
                    //if true, ask question for fainting
                    if(result == 1){
                        result = askQuestion(*clvarlt[backClauseNum + 2]);
                        //if all true, add pulmonary stenosis to conclusion stack and set diagnosed to true
                        if(result == 1){
                            backChainConclusions.push("Pulmonary Stenosis");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;
                        }
                    }
                }




            }
            break;
            case 2:{
            cout << "Checking Cardiac Arrest." << endl;
            /*rule 20*/
            backClauseNum = 4* (20 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question for palpatations
                //if true ask question for irregular heartbeat
                if(result == 1){
                    result = askQuestion(*clvarlt[backClauseNum + 1]);
                    //if both true then they are at risk for heart attack
                    if(result == 1){
                            backChainConclusions.push("Cardiac Arrest");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }
                }

            /*rule 30*/
            backClauseNum = 4* (30 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question for angina
                //if true ask question for irregular heartbeat
                if(result == 1){
                    result = askQuestion(*clvarlt[backClauseNum + 1]);
                    //if both true then at risk of heart attack
                    if(result == 1){
                            backChainConclusions.push("Cardiac Arrest");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }
                }
            /*rule 40*/
            backClauseNum = 4* (40 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question for Shortness of breath
                //if true ask question for Sudden Shortness of breath
                if(result == 1){
                    result = askQuestion(*clvarlt[backClauseNum + 1]);
                    //if true ask question for palpatations
                    if(result == 1){
                        result = askQuestion(*clvarlt[backClauseNum + 2]);
                        //if both true then they are at risk for heart attack
                        if(result == 1){
                                backChainConclusions.push("Cardiac Arrest");
                                string test = backChainConclusions.top();
                                cout << "You are suffering from " << test << endl;
                                diagnosed = true;
                                break;

                        }
                    }
                }

                        //if both true then at risk of cardiac arrest
            /*rule 50*/
            backClauseNum = 4* (50 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question for Fainting
                //if true ask question for irregular heartbeat
                    //if both true then at risk of cardiac arrest.
                if(result == 1){
                    result = askQuestion(*clvarlt[backClauseNum + 1]);
                        if(result == 1){
                                backChainConclusions.push("Cardiac Arrest");
                                string test = backChainConclusions.top();
                                cout << "You are suffering from " << test << endl;
                                diagnosed = true;
                                break;

                        }

                }
            /*rule 60*/
            backClauseNum = 4* (60 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question for Irregular heartbeat
                //if true ask question for dizziness
                    //if both true then at risk of cardiac arrest
                if(result == 1){
                    result = askQuestion(*clvarlt[backClauseNum + 1]);
                        if(result == 1){
                                backChainConclusions.push("Cardiac Arrest");
                                string test = backChainConclusions.top();
                                cout << "You are suffering from " << test << endl;
                                diagnosed = true;
                                break;

                        }

                }
            /*rule 70*/
            backClauseNum = 4* (70 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question for angina
                //if true ask question for wheezing
                    //if true ask question for palpatations
                        //if all true then at risk of cardiac arrest
            if(result == 1){
                    result = askQuestion(*clvarlt[backClauseNum + 1]);
                    if(result == 1){
                        result = askQuestion(*clvarlt[backClauseNum + 2]);
                        if(result == 1){
                                backChainConclusions.push("Cardiac Arrest");
                                string test = backChainConclusions.top();
                                cout << "You are suffering from " << test << endl;
                                diagnosed = true;
                                break;

                        }
                    }
                }
            /*rule 80*/
            backClauseNum = 4* (80 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question for wheezing
                //if true ask question for palpations
                    //if both true then at risk of cardiac arrest
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                    if(result == 1){
                            backChainConclusions.push("Cardiac Arrest");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }

            }



            }
            break;
            case 3:{
            cout << "Checking Congenital Heart disease." << endl;
            /*rule 90*/
            backClauseNum = 4* (90 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question for murmur
                //if true, ask question for swelling
                    //if true, ask question for swelling in lunges or stomach
                        //if all true, add congenital heart disease to conclusion stack, set diagnosed to true
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                if(result == 1){
                    result = askQuestion(*clvarlt[backClauseNum + 2]);
                    if(result == 1){
                            backChainConclusions.push("Congenital Heart Disease");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }
                }
            }
            /*rule 100*/
            backClauseNum = 4* (100 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question for blue tinge to skin
                //if true ask question for murmur
                    //if no, ask question for irregular heartbeat
                    //if yes, then add congenital heart disease to conclusion stack, set diagnosed to true
                        //if no, ask question for shortness of breath
                        //if yes, then add congenital heart disease to conclusion stack, set diagnosed to true
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                if(result == 1){
                    backChainConclusions.push("Congenital Heart Disease");
                    string test = backChainConclusions.top();
                    cout << "You are suffering from " << test << endl;
                    diagnosed = true;
                    break;
                }
                else{
                        result = askQuestion(*clvarlt[backClauseNum + 2]);
                        if(result == 1){
                            backChainConclusions.push("Congenital Heart Disease");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;
                        }
                        else{
                            result = askQuestion(*clvarlt[backClauseNum + 3]);
                            if(result == 1){
                                backChainConclusions.push("Congenital Heart Disease");
                                string test = backChainConclusions.top();
                                cout << "You are suffering from " << test << endl;
                                diagnosed = true;
                                break;
                            }
                        }

                }



            }

            /*rule 110*/
            backClauseNum = 4* (110 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question for Swelling in Lunges/Stomach
                //if true ask question for irregular heartbeat
                    //if both true then they have Congenital Heart disease
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                    if(result == 1){
                            backChainConclusions.push("Congenital Heart Disease");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }

            }



            }
            break;
            case 4:{
            cout << "Checking Dilated Cardiomyopathy." << endl;
            /*rule 120*/
            backClauseNum = 4* (120 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question for recent heart attack
                //if true ask question for swelling
                    //if true ask question for swelling in legs
                        //if true they have dilated cardiomypathy
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                if(result == 1){
                    result = askQuestion(*clvarlt[backClauseNum + 2]);
                    if(result == 1){
                            backChainConclusions.push("Dilated Cardiomyopathy");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }
                }
            }
            /*rule 130*/
            backClauseNum = 4* (130 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question for Irregular heartbeat
                //if true ask question for Swelling
                    //if true ask question for Swelling in legs
                        //if both true then disease is Dilated Cardiomyopathy
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                if(result == 1){
                    result = askQuestion(*clvarlt[backClauseNum + 2]);
                    if(result == 1){
                            backChainConclusions.push("Dilated Cardiomyopathy");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }
                }
            }
            /*rule 140*/
            backClauseNum = 4* (140 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question for Irregular heartbeat
                //if true ask question for Shortness of breath
                    //if true ask question for Shortness of breath when lying down or trying to sleep
                        //if both true then they have Dilated Cardiomyopathy
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                if(result == 1){
                    result = askQuestion(*clvarlt[backClauseNum + 2]);
                    if(result == 1){
                            backChainConclusions.push("Dilated Cardiomyopathy");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }
                }
            }


            }
            break;
            case 5:{
            cout << "Checking Coronary Artery disease." << endl;
            /*rule 150*/
            backClauseNum = 4* (150 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question for Irregular Heartbeat
                //if true ask question for angina
                    //if true ask question for palpitations
                        //if all true then they have Coronary Artery disease
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                if(result == 1){
                    result = askQuestion(*clvarlt[backClauseNum + 2]);
                    if(result == 1){
                            backChainConclusions.push("Coronary Artery Disease");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }
                }
            }



            }
            break;
            case 6:{
            cout << "Checking Heart Arrhythmia." << endl;
            /*rule 160*/
            backClauseNum = 4* (160 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question for palpatations
                //if true ask question for angina
                    //if true ask question for Fluttery feeling in chest
                        //if all true then they have Heart Arrhythmia
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                if(result == 1){
                    result = askQuestion(*clvarlt[backClauseNum + 2]);
                    if(result == 1){
                            backChainConclusions.push("Heart Arrhythmia");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }
                }
            }
            /*rule 170*/
            backClauseNum = 4* (170 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask questions for Slow heartbeat
                //if true ask question for angina
                    //if true ask question for palpitations
                        //if all true, add Heart Arrhythmia to conclusion stack and set diagnosed to true.
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                if(result == 1){
                    result = askQuestion(*clvarlt[backClauseNum + 2]);
                    if(result == 1){
                            backChainConclusions.push("Heart Arrhythmia");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }
                }
            }



            }
            break;
            case 7:{
            cout << "Checking Stroke." << endl;
            /*rule 180*/
            backClauseNum = 4* (180 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question about slurred/incoherent speech
                //if yes ask if they are confused
                    //if both yes, then they are suffering from a stroke
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                    if(result == 1){
                            backChainConclusions.push("Stroke");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }

            }
            /*rule 190*/
            backClauseNum = 4* (190 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question about slurred/incoherent speech
                //if yes, ask about dizziness
                    //if both yes, then they are suffering from stroke
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                    if(result == 1){
                            backChainConclusions.push("Stroke");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }

            }
            /*rule 200*/
            backClauseNum = 4* (200 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question about slurred/incoherent speech
                //if yes, ask about loss of motor control
                    //if both yes, then they are suffering from stroke
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                    if(result == 1){
                            backChainConclusions.push("Stroke");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }

            }
            /*rule 210*/
            backClauseNum = 4* (210 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question about dizziness
                //if yes, ask about loss of motor control
                    //if both yes, then they are suffering from stroke

            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                    if(result == 1){
                            backChainConclusions.push("Stroke");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }

            }



            /*rule 220*/
            backClauseNum = 4* (210 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question about numbness in limbs
                //if yes, ask about loss of sight
                    //if both yes, then they are suffering from stroke
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                    if(result == 1){
                            backChainConclusions.push("Stroke");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }

            }


            /*rule 230*/
            backClauseNum = 4* (230 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask about dizziness
                //if yes, ask about lack of balance
                    //if yes, ask about confusion
                        //if all yes, then they are suffering from stroke
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                if(result == 1){
                    result = askQuestion(*clvarlt[backClauseNum + 2]);
                    if(result == 1){
                            backChainConclusions.push("Stroke");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }
                }
            }
            /*rule 240*/
            backClauseNum = 4* (240 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask about lack of balance
                //if yes, ask about numbness in limbs
                    //if both yes, then suffering from stroke.
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                    if(result == 1){
                            backChainConclusions.push("Stroke");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }

            }


            }

            break;
            case 8:{
            cout << "Checking Peripheral Artery Disease." << endl;
            /*rule 250*/
            backClauseNum = 4* (250 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question for Cramping at joints
                //if true ask question for ulcers
                    //if both true then they have Peripheral artery disease
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                    if(result == 1){
                            backChainConclusions.push("Peripheral Artery Disease");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }

            }
            /*rule 260*/
            backClauseNum = 4* (260 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question for Cramping at joints
                //if true ask question for drop in body temp
                    //if both true then they have Peripheral artery disease.
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                    if(result == 1){
                            backChainConclusions.push("Peripheral Artery Disease");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }

            }
            /*rule 270*/
            backClauseNum = 4* (270 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question regarding numbness in limbs
                //if yes, ask question for loss of hair at extremities
                    //if both yes, then they have peripheral artery disease
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                    if(result == 1){
                            backChainConclusions.push("Peripheral Artery Disease");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }

            }
            /*rule 280*/
            backClauseNum = 4* (280 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question regarding drop in body temp
                //if yes, ask for ulcers
                    //if both yes, then they have peripheral artery disease
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                    if(result == 1){
                            backChainConclusions.push("Peripheral Artery Disease");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }

            }
            /*rule 290*/
            backClauseNum = 4* (290 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question regarding drop in body temp
                //if yes, ask for cramping in thighs and calves
                    //if both yes, then they have peripheral artery disease
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                    if(result == 1){
                            backChainConclusions.push("Peripheral Artery Disease");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }

            }
            /*rule 300*/
            backClauseNum = 4* (300 / 10 - 1);
            result = askQuestion(*clvarlt[backClauseNum]);
            //ask question regarding cramping at joints
                //if yes, ask for cramping in thighs and calves
                    //if both yes, then they have peripheral artery disease
            if(result == 1){
                result = askQuestion(*clvarlt[backClauseNum + 1]);
                    if(result == 1){
                            backChainConclusions.push("Peripheral Artery Disease");
                            string test = backChainConclusions.top();
                            cout << "You are suffering from " << test << endl;
                            diagnosed = true;
                            break;

                    }

            }


            }
            break;

        }


        i++;
    }


    if(!backChainConclusions.empty()){
            dName = backChainConclusions.top();
            /*8 Disease
            Congenital Heart Disease
            Coronary Artery Disease
            Heart Arrhythmia
            Dilated Cardiomyopathy
            Pulmonary Stenosis
            Peripheral Artery Disease
            Cardiac Arrest
            Stroke
            */


          /*theres only one rule for the rule base and clVarLt of the forward chaining
          however we're still going to calculate the rule number as if theres more


          this formula
          Rule # = [({Quotient  (Clause # / 4)} +1) * 10]


          modified to this
          Rule # = [({Quotient  (Clause # / 4)} +1) * 10]

          is what we'll use


          theres only one rule, so in this case we know the clause number = 0
          however in any other case we would need to use a linear search to find the clause num

          */
          int ruleNum = ((0 / 4) +1) * 10;
          //^^ Will always be ten



          switch(ruleNum){
            case 10:{
              if(*forwardClVarLt[0] == "Congenital Heart Disease")
              {
                  cout << "For " << dName << " Treatment will include. \n" << endl;

                  forwardConclusions.push("Medications: Beta Blockers, Digoxin, Antiplatelets \nMedical procedure: Cardiac Catheterization \nSurgery: Intracardiac repair, Heart Transplant");

                  cout << forwardConclusions.front() << endl;
              }
              else if (*forwardClVarLt[0] == "Coronary Artery Disease")
              {
                  cout << "For " << dName << " Treatment will include. \n" << endl;

                  forwardConclusions.push("Self-Care: Quit Smoking, Weight loss, Exercise, Low fat diet \nMedications: Statin, Anticoagulant, Antianginal \nMedical procedure: Coronary Stent, Coronary Angioplasty \nSurgery: Coronary artery bypass");

                  cout << forwardConclusions.front() << endl;
              }
              else if (*forwardClVarLt[0] == "Heart Arrhythmia")
              {
                  cout << "For " << dName << " Treatment will include. \n" << endl;

                  forwardConclusions.push("Self-Care: Cardiac Monitoring \nMedications: Antiarrhythmic, Dietary Supplements, Beta Blockers \nMedical procedure: Cardioversion, Radio-frequency Ablation \nDevices: Pacemaker, Implantable cardioverter-defibrillator");

                  cout << forwardConclusions.front() << endl;
              }
              else if (*forwardClVarLt[0] == "Dilated Cardiomyopathy")
              {
                  cout << "For " << dName << " Treatment will include. \n" << endl;

                  forwardConclusions.push("Therapies: Bi-ventricular Pacemaker, ICD, LVAD \nMedication: Entresto, Diuretics, Anticoagulants \nSurgery: Heart Transplant");

                  cout << forwardConclusions.front() << endl;
              }
              else if (*forwardClVarLt[0] == "Pulmonary Stenosis")
              {
                  cout << "For " << dName << " Treatment will include. \n" << endl;

                  forwardConclusions.push("Medical Procedure: Balloon Valvuloplasty, Pulmonary Valve Replacement \nSurgery: Heart Transplant");

                  cout << forwardConclusions.front() << endl;
              }
              else if (*forwardClVarLt[0] == "Peripheral Artery Disease")
              {
                  cout << "For " << dName << " Treatment will include. \n" << endl;

                  forwardConclusions.push("Self-care: Exercise \nMedications: Statin, Vasodilator \nMedical procedure: Angioplasty");

                  cout << forwardConclusions.front() << endl;
              }
              else if (*forwardClVarLt[0] == "Cardiac Arrest")
              {
                  cout << "For " << dName << " Treatment will include. \n" << endl;

                  forwardConclusions.push("Supportive care: Defibrillation, CPR \nMedications: Blood pressure support \nMedical procedure: Coronary Catheterization \nDevices: Implantable cardioverter-defilbrillator");

                  cout << forwardConclusions.front() << endl;

              }
              else if (*forwardClVarLt[0] == "Stroke")
              {
                  cout << "For " << dName << " Treatment will include. \n" << endl;

                  forwardConclusions.push("Therapies: Speech, Physical \nSupportive Care: Cardiac Monitoring \nMedication: Alteplase, Statin \nSurgery: Carotid endarterectomy");

                  cout << forwardConclusions.front() << endl;
              }
            }
          }
        cout << endl;
    }
    else{
        cout << endl << "No diagnosis found, have a good day." << endl;
    }






    cout << "Would you like to run the program again? Y or y for yes, N or n for no" << endl;
    cin >> contin;
    while(contin != 'y'&&contin != 'Y'&&contin != 'n'&&contin != 'N'){
        cout << "Incorrect entry. Y or y for yes, N or n for no" << endl;
        cin >> contin;
    }
    if(contin == 'n'||contin == 'N'){
        cout << "Thank you for using this application, goodbye." << endl;
        return 0;
    }

    }

    return 0;

}


//intializes our rule list, fact list, and clause fact list with the proper data
void initialize(){

    //***********************************************************
    //Building our symptoms
    //***********************************************************



    //Murmur
    varlt[0].name = "Murmur";
    varlt[0].question = "Are you suffering from a murmur?";
    varlt[0].status = -1;

    //Irregular Heartbeat
    varlt[1].name = "Irregular Heartbeat";
    varlt[1].question = "Are you suffering from an Irregular Heartbeat?";
    varlt[1].status = -1;

    //Slow heartbeat
    varlt[2].name = "Slow heartbeat";
    varlt[2].question = "Are you suffering from a Slow heartbeat?";
    varlt[2].status = -1;

    //Blue tinge on skin
    varlt[3].name = "Blue tinge on skin";
    varlt[3].question = "Have you noticed a blue tinge to your skin?";
    varlt[3].status = -1;

    //Angina
    varlt[4].name = "Angina";
    varlt[4].question = "Have you been suffering from a pain in your chest?";
    varlt[4].status = -1;

    //Palpatations
    varlt[5].name = "Palpatations";
    varlt[5].question = "Have you been suffering from palpatations?";
    varlt[5].status = -1;

    //Fainting
    varlt[6].name = "Fainting";
    varlt[6].question = "Have you fainted recently?";
    varlt[6].status = -1;

    //Wheezing
    varlt[7].name = "Wheezing";
    varlt[7].question = "Have you been Wheezing recently?";
    varlt[7].status = -1;

    //Shortness of breath (unspecified)
    varlt[8].name = "Shortness of breath (unspecified)";
    varlt[8].question = "Have you experienced Shortness of breath?";
    varlt[8].status = -1;

    //Sudden shortness of breath
    varlt[9].name = "Sudden shortness of breath";
    varlt[9].question = "Have you experienced a Sudden shortness of breath recently?";
    varlt[9].status = -1;

    //Shortness of breath when trying to sleep
    varlt[10].name = "Shortness of breath when trying to sleep";
    varlt[10].question = "Do you suffer from Shortness of breath when trying to sleep?";
    varlt[10].status = -1;

    //Fluttery Feeling in chest
    varlt[11].name = "Fluttery Feeling in chest";
    varlt[11].question = "Do you experience Fluttery Feeling in the chest?";
    varlt[11].status = -1;

    //Swelling (unspecified)
    varlt[12].name = "Swelling (unspecified)";
    varlt[12].question = "Have you noticed Swelling?";
    varlt[12].status = -1;

    //Swelling in legs
    varlt[13].name = "Swelling in legs";
    varlt[13].question = "Have you noticed Swelling in the legs?";
    varlt[13].status = -1;

    //Swelling in Lunges/Stomach
    varlt[14].name = "Swelling in Lunges/Stomach";
    varlt[14].question = "Have you noticed Swelling in the Lunges/Stomach?";
    varlt[14].status = -1;

    //Cough
    varlt[15].name = "Cough";
    varlt[15].question = "Have you been Coughing recently?";
    varlt[15].status = -1;

    //Wheezing (severe/sudden cough)
    varlt[16].name = "Wheezing (severe/sudden cough)";
    varlt[16].question = "Do you experience Severe/Sudden Wheezing?";
    varlt[16].status = -1;

    //Nausea
    varlt[17].name = "Nausea";
    varlt[17].question = "Do you feel Nausea?";
    varlt[17].status = -1;

    //Dizziness
    varlt[18].name = "Dizziness";
    varlt[18].question = "Are you suffering from Dizziness?";
    varlt[18].status = -1;

    //Recent heart attack (cardiac arrest)
    varlt[19].name = "Recent heart attack (cardiac arrest)";
    varlt[19].question = "Have you suffered from a Recent Heart Attack?";
    varlt[19].status = -1;

    //Numbness in limbs
    varlt[20].name = "Numbness in limbs";
    varlt[20].question = "Do your limbs feel numb?";
    varlt[20].status = -1;

    //Loss of hair at extremities
    varlt[21].name = "Loss of hair at extremities";
    varlt[21].question = "Have you lost hair at your arms, legs, fingers, toes etc.?";
    varlt[21].status = -1;

    //Drop in body temp at extremities
    varlt[22].name = "Drop in body temp at extremities";
    varlt[22].question = "Have you experienced a coldness in your arms, legs, fingers, toes etc.?";
    varlt[22].status = -1;

    //Cramping at joints
    varlt[23].name = "Cramping at joints";
    varlt[23].question = "Have you experienced cramping at your joints? (Hips, shoulders, elbows, knees)";
    varlt[23].status = -1;

    //Cramping in thighs or calves
    varlt[24].name = "Cramping in thighs or calves";
    varlt[24].question = "Have you experienced cramping in thighs or calves?";
    varlt[24].status = -1;

    //Slurred or incoherent speech
    varlt[25].name = "Slurred or incoherent speech";
    varlt[25].question = "Is your speech incoherent or slurred?";
    varlt[25].status = -1;

    //Lack of balance
    varlt[26].name = "Lack of balance";
    varlt[26].question = "Have you experienced a lack of balance";
    varlt[26].status = -1;

    //Loss of motor control
    varlt[27].name = "Loss of motor control";
    varlt[27].question = "Have you experienced a loss of motor control?";
    varlt[27].status = -1;

    //Confusion
    varlt[28].name = "Confusion";
    varlt[28].question = "Have you suffered from a sudden confusion?";
    varlt[28].status = -1;

    //Loss of sight
    varlt[29].name = "Loss of sight";
    varlt[29].question = "Have you suffered from a loss of sight (partial or full)?";
    varlt[29].status = -1;

    //Ulcers
    varlt[30].name = "Ulcers";
    varlt[30].question = "Have you experienced Ulcers recently?";
    varlt[30].status = -1;



    //***********************************************************
    //Dividing up our clause variable list for the backward chain
    //***********************************************************

    /*According to the formula:
    CLAUSE NUMBER = 4* (RULE NUMBER  / 10 - 1) + 1
    We will be dividing up our clause variable list

    CLAUSE NUMBER = 4* (RULE NUMBER  / 10 - 1)
    this formula will be to find the index in the clvarlt array (because arrays are base 0)
    */

    /*rule 10*/
    clvarlt[0] = &varlt[0]; // points to murmur
    clvarlt[1] = &varlt[1]; // points to irregular heartbeat
    clvarlt[2] = &varlt[6]; // points to fainting
    //empty

    /*rule 20*/
    clvarlt[4] = &varlt[5]; // points to palpatations
    clvarlt[5] = &varlt[1]; // points to irregular heartbeat
    //empty
    //empty

    /*rule 30*/
    clvarlt[8] = &varlt[4]; // points to angina
    clvarlt[9] = &varlt[1]; // points to irregular heartbeat
    //empty
    //empty

    /*rule 40*/
    clvarlt[12] = &varlt[8]; // points to shortness of breath
    clvarlt[13] = &varlt[9]; // points to sudden shortness of breath
    clvarlt[14] = &varlt[5]; // points to palpatations
    //empty

    /*rule 50*/
    clvarlt[16] = &varlt[6]; // points to fainting
    clvarlt[17] = &varlt[1]; // points to irregular heartbeat
    //empty
    //empty

    /*rule 60*/
    clvarlt[20] = &varlt[1]; // points to irregular heartbeat
    clvarlt[21] = &varlt[18]; // points to dizziness
    //empty
    //empty

    /*rule 70*/
    clvarlt[24] = &varlt[4]; // points to angina
    clvarlt[25] = &varlt[7]; // points to wheezing
    clvarlt[26] = &varlt[5]; // points to palpatations
    //empty

    /*rule 80*/
    clvarlt[28] = &varlt[7]; // points to wheezing
    clvarlt[29] = &varlt[5]; // points to palpatations
    //empty
    //empty

    /*rule 90*/
    clvarlt[32] = &varlt[0]; // points to murmur
    clvarlt[33] = &varlt[12]; // points to swelling
    clvarlt[34] = &varlt[14]; // points to swelling in lunges or stomach
    //empty

    /*rule 100*/
    clvarlt[36] = &varlt[3]; // points to blue tinge
    clvarlt[37] = &varlt[0]; // points to murmur
    clvarlt[38] = &varlt[1]; // points to irregular heartbeat
    clvarlt[39] = &varlt[8]; // points to shortness of breath

    /*rule 110*/
    clvarlt[40] = &varlt[14]; // points to swelling in lunges or stomach
    clvarlt[41] = &varlt[1]; // points to irregular heartbeat
    //empty
    //empty

    /*rule 120*/
    clvarlt[44] = &varlt[19]; // points to recent heart attack
    clvarlt[45] = &varlt[12]; // points to swelling
    clvarlt[46] = &varlt[13]; // points to swelling in legs
    //empty

    /*rule 130*/
    clvarlt[47] = &varlt[1]; // points to irregular heartbeat
    clvarlt[48] = &varlt[12]; // points to swelling
    clvarlt[49] = &varlt[13]; // points to swelling in legs
    //empty

    /*rule 140*/
    clvarlt[52] = &varlt[1]; // points to irregular heartbeat
    clvarlt[53] = &varlt[8]; // points to shortness of breath
    clvarlt[54] = &varlt[10]; // points to shortness of breath when lying down
    //empty

    /*rule 150*/
    clvarlt[56] = &varlt[1]; // points to irregular heartbeat
    clvarlt[57] = &varlt[4]; // points to angina
    clvarlt[58] = &varlt[5]; // points to palpatations
    //empty

    /*rule 160*/
    clvarlt[60] = &varlt[5]; // points to palpatations
    clvarlt[61] = &varlt[4]; // points to angina
    clvarlt[62] = &varlt[11]; // points to fluttery feeling in chest
    //empty

    /*rule 170*/
    clvarlt[64] = &varlt[2]; // points to slow heartbeat
    clvarlt[65] = &varlt[4]; // points to angina
    clvarlt[66] = &varlt[5]; // points to palpatations
    //empty

    /*rule 180*/
    clvarlt[68] = &varlt[25]; // points to slurring
    clvarlt[69] = &varlt[28]; // points to confusion
    //empty
    //empty

    /*rule 190*/
    clvarlt[72] = &varlt[25]; // points to slurring
    clvarlt[73] = &varlt[18]; // points to dizziness
    //empty
    //empty

    /*rule 200*/
    clvarlt[76] = &varlt[25]; // points to slurring
    clvarlt[77] = &varlt[27]; // points to loss of motor control
    //empty
    //empty

    /*rule 210*/
    clvarlt[80] = &varlt[18]; // points to dizziness
    clvarlt[81] = &varlt[27]; // points to loss of motor control
    //empty
    //empty

    /*rule 220*/
    clvarlt[84] == &varlt[20]; // points to numbness in limbs
    clvarlt[85] == &varlt[29]; // points to loss of sight
    //empty
    //empty

    /*rule 230*/
    clvarlt[88] = &varlt[18]; // points to dizziness
    clvarlt[89] = &varlt[26]; // points to lack of balance
    clvarlt[90] = &varlt[28]; // points to confusion
    //empty

    /*rule 240*/
    clvarlt[92] = &varlt[26]; // points to lack of balance
    clvarlt[93] = &varlt[20]; // points to numbness in limbs
    //empty
    //empty

    /*rule 250*/
    clvarlt[96] = &varlt[23]; // points to cramping at joints
    clvarlt[97] = &varlt[30]; // points to ulcers
    //empty
    //empty

    /*rule 260*/
    clvarlt[100] = &varlt[23]; // points to cramping at joints
    clvarlt[101] = &varlt[22]; // points to drop in body temp at extremities
    //empty
    //empty

    /*rule 270*/
    clvarlt[104] = &varlt[20]; // points to numbness in limbs
    clvarlt[105] = &varlt[21]; // points to loss of hair at extremities
    //empty
    //empty

    /*rule 280*/
    clvarlt[108] = &varlt[22]; // points to drop in body temp at extremities
    clvarlt[109] = &varlt[30]; // points to ulcers
    //empty
    //empty

    /*rule 290*/
    clvarlt[112] = &varlt[22]; // points to drop in body temp at extremities
    clvarlt[113] = &varlt[24]; // points to cramping in thighs and calves
    //empty
    //empty

    /*rule 300*/
    clvarlt[116] = &varlt[23]; // points to cramping at joints
    clvarlt[117] = &varlt[24]; // points to cramping in thighs and calves
    //empty
    //empty





    /*Forward Chaining clause variable list*/

    forwardClVarLt[0] = &dName;







    return;
}


//retrieves the question from an inputted fact structure (passed by reference), outputs it, and sets the facts status according to the answer. Returns the facts status as well.
int askQuestion(fact &input){

    if(input.status != -1){
        cout << "Symptom: " << input.name << " status confirmed." << endl;
        if(input.status == 1){
            cout << "Symptom present." << endl;
        }
        if(input.status == 0){
            cout << "Symptom absent." << endl;
        }
        return input.status;
    }

    char answer;
    cout << input.question << endl;
    cout << "Y or y for yes, N or n for no." << endl;
    cin >> answer;
    cout << endl;
    while(answer != 'y'&&answer != 'Y'&&answer != 'n'&&answer != 'N'){
        cout << "Incorrect entry. Y or y for yes, N or n for no" << endl;
        cin >> answer;
    }
    if(answer == 'n'||answer == 'N'){
        input.status = 0;
    }
    else if(answer == 'y'||answer == 'Y'){
        input.status = 1;
    }
    return input.status;

}
