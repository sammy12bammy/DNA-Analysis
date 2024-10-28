#include<iostream>

using namespace std;

bool isValidBase(char base){
    return (base =='A' || base == 'C' || base == 'G' || base =='T');
}

bool isValidStrand(string strand){
    //len is the length of the param strand
    int len = strand.length();
    //returns false if the length is 0
    if(len == 0){
        return false;
    }
    //iterates through the string, calling isValidBase for every char
    for(int i = 0; i < len; i++){
        if(!isValidBase(strand[i])){
            return false;
        }
    }
    //if no invalid character found, returns true
    return true;
}
double strandSimilarity(string strand1, string strand2){
    /*
    //checks if the strands are valid
    if(!isValidStrand(strand1) || !isValidStrand(strand2)){
        return 0;
    }
    */
    //return 0 if the 2 strands are off different lengths
    if(strand1.length() != strand2.length()){
        return 0;
    }
    //length of the strands
    int len = strand1.length();
    //setting up variables for the char being check
    int index1, index2;
    //set up a variable to keep track of how many matches
    int count = 0;
    for(int i = 0; i < len; i++){
        index1 = strand1[i];
        index2 = strand2[i];
        //if the 2 chars are identical, increment count
        if(index1 == index2){
            count++;
        }
    }
    //return a casted double of the 2 ints
    return (double)count / (double)len;
}
int bestStrandMatch(string input_strand, string target_strand){
    //checks if the input is less than the target, and if it is
    //returns -1    
    if(input_strand.length() < target_strand.length()){
        cout<<"Best similarity score: 0.0"<<endl;
        return -1;       
    }  
    //setting up variables
    double best_score = 0;
    int best_score_index = 0;
    int in_len = input_strand.length();
    int tar_len = target_strand.length();
    //iterate through the input length as much as possible
    for(int i = 0; i <= in_len - tar_len; i++){
        //substring of input that is the same length as the target
        string sub = input_strand.substr(i, target_strand.length());
        //calling strandSimilarity to compare the sub and the target to the current best score
        if(strandSimilarity(sub, target_strand) > best_score){
            //reassigning the variables if they are higher
            best_score = strandSimilarity(sub, target_strand);
            best_score_index = i;
        }
    }
    //checks if the strands are the same length, the for loop above will not run if they
    //are the same length
    if(input_strand.length() == target_strand.length()){
        best_score = strandSimilarity(input_strand, target_strand);
    }
    cout<<"Best similarity score: "<<best_score<<endl;
    return best_score_index;
}

void identifyMutations(string input_strand, string target_strand){
    //checks if they are the same
    if(input_strand == target_strand){
        cout<<"Best similarity score: 1"<<endl;
        cout<<"Best alignment index: 0"<<endl;
        cout<<"No mutations found."<<endl;
        return;
    }
    //initialize length vars
    int in_len = input_strand.length();
    int tar_len = target_strand.length();
    //if the lengths are the same, only sub can occur
    if(in_len == tar_len){
        //print out the similarity and the alignment score
        int best_index = bestStrandMatch(input_strand, target_strand);
        cout<<"Best alignment index: "<<best_index<<endl;
        //chars of the string that are going to be checked
        char in_cur;
        char tar_cur;
        for(int i = 0; i < in_len; i++){
            in_cur = input_strand[i];
            tar_cur = target_strand[i];
            if(in_cur != tar_cur){
                cout<<"Substitution at position "<<i+1<<": "<<in_cur<<" -> "<<tar_cur<<endl;
            }
        }
        //breaks out of function
        return;
    }
    //find the longest string
    string longest, shortest;
    if(in_len > tar_len){
        longest = input_strand;
        shortest = target_strand;
    } else {
        longest = target_strand;  
        shortest = input_strand;    
    }  
    //inseration can occur if the input is less than the output
    if(in_len < tar_len){
        int best_index = bestStrandMatch(target_strand, input_strand);
        cout<<"Best alignment index: "<<best_index<<endl;
        //create blank string to allign, same length as longer string
        string temp = "";
        int count = 0;
        for(int i = 0; i < best_index; i++){
            temp += '-';
        }
        for(int i = best_index; i < best_index + in_len; i++){
            temp += input_strand[count];
            count++;
        } 
        for(int i = best_index + in_len; i < tar_len; i++){
            temp += '-';
        }
        //loops through and checks against the strings
        for(int i = 0; i < tar_len; i++){
            if(temp[i] == '-'){
                //insertion took place
                cout<<"Insertion at position "<<i+1<<": "<<target_strand[i]<<" is inserted in target strand"<<endl;
            } else if(temp[i] != target_strand[i]){
                //sub took places
                cout<<"Substitution at position "<<i+1<<": "<<temp[i]<<" -> "<<target_strand[i]<<endl;
            }
        }
    } else {
        //same code as above but different strand length
        int best_index = bestStrandMatch(input_strand, target_strand);
        cout<<"Best alignment index: "<<best_index<<endl;
        string temp = "";

        int count = 0;
        for(int i = 0; i < best_index; i++){
            temp += '-';
        }
        for(int i = best_index; i < best_index + tar_len; i++){
            temp += shortest[count];
            count++;
        } 
        for(int i = best_index + tar_len; i < in_len; i++){
            temp += '-';
        }
        
        for(int i = 0; i < in_len; i++){
            if(temp[i] == '-'){
                //deletion
                cout<<"Deletion at position "<<i+1<<": "<<longest[i]<<" is missing in input strand"<<endl;
            } else if(temp[i] != longest[i]){
                //substitution
                cout<<"Substitution at position "<<i+1<<": "<<temp[i]<<" -> "<<longest[i]<<endl;
            }
        }       
    }
}

void transcribeDNAtoRNA(string strand){
    string temp = "";
    int len = strand.length();

    for(int i = 0; i < len; i++){
        if(strand[i] == 'T'){
            temp += 'U';
        } else {
            temp += strand[i];
        }
    }
    cout<<temp<<endl;
}

void reverseComplement(string strand){
    //string that is going to be swapped
    string swap = "";
    //string that is going ti be reversed
    string reverse = "";
    int len = strand.length();
    //swaps chars
    for(int i = 0; i < len; i++){
        char cur = strand[i];
        switch(cur){
            case 'A':
                swap += 'T';
                break;
            case 'T':
                swap += 'A';
                break;
            case 'G':
                swap += 'C';
                break;
            case 'C':
                swap += 'G';
                break;
        }
    }
    //reverses string
    for(int i = len - 1; i >= 0; i--){
        reverse += swap[i];
    }
    cout<<reverse<<endl;
}

void getCodingFrames(string strand){
    //loop through until you find a atg
    //when you find a atg, skip the 3 chars and check for either (TAA, TAG, or TGA)
    //empty string adding onto each char
    //interate loop
    int len = strand.length();
    //amount of valid frames
    int count = 0;
    for(int i = 0; i < len - 3; i++){
        //if you found correct first 3
        if(strand[i] == 'A' && strand[i+1] == 'T' && strand[i+2] == 'G'){   
            //loop starts after the first 3 and incremnts by 3
            for(int j = i + 3; j < len - 2; j += 3){
                string next3 = strand.substr(j, 3);
                //if a end is found
                if(next3 == "TAA" || next3 == "TAG" || next3 == "TGA"){
                    // if valid, print
                    string out = strand.substr(i, j - i + 3);
                    cout << out << endl;
                    //increment the amount of frames for the rest statemnt
                    count++;
                    i = j + 2;
                    break; 
                }
            }   
        }
    }
    if(count == 0){
        cout<<"No reading frames found."<<endl;
    }
}

void printMenu(){
    cout<<"--- DNA Analysis Menu ---"<<endl;
    cout<<"1. Calculate the similarity between two sequences of the same length"<<endl;
    cout<<"2. Calculate the best similarity between two sequences of either equal or unequal length"<<endl;
    cout<<"3. Identify mutations"<<endl;
    cout<<"4. Transcribe DNA to RNA"<<endl;
    cout<<"5. Find the reverse complement of a DNA sequence"<<endl;
    cout<<"6. Extract coding frames"<<endl;
    cout<<"7. Exit"<<endl;
    cout<<"Please enter your choice (1 - 7):"<<endl;
}
int main(){
    string first, second;

    int input = -1;
    while(input != 7){
        printMenu();
        cin>>input;
        switch(input){
            case 1:
                cout<<"Enter the first DNA sequence:"<<endl;
                cin>>first;
                while(!isValidStrand(first)){
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cout<<"Enter the first DNA sequence:"<<endl;
                    cin>>first;
                }   
                cout<<"Enter the second DNA sequence:"<<endl;
                cin>>second;
                while(!isValidStrand(second)){
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cout<<"Enter the second DNA sequence:"<<endl;
                    cin>>second;
                }
                if(first.length() != second.length()){
                    cout<<"Error: Input strands must be of the same length."<<endl;
                    break;
                } 
                cout<<"Similarity score: "<<strandSimilarity(first, second)<<endl;
                break;
            case 2:
                cout<<"Enter the first DNA sequence:"<<endl;
                cin>>first;
                while(!isValidStrand(first)){
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cout<<"Enter the first DNA sequence:"<<endl;
                    cin>>first;
                }   
                cout<<"Enter the second DNA sequence:"<<endl;
                cin>>second;
                while(!isValidStrand(second)){
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cout<<"Enter the second DNA sequence:"<<endl;
                    cin>>second;
                }
                bestStrandMatch(first,second);
                break;
            case 3:
                cout<<"Enter the first DNA sequence:"<<endl;
                cin>>first;
                cout<<"Enter the second DNA sequence:"<<endl;
                cin>>second;
                identifyMutations(first, second);
                break;
            case 4:
                cout<<"Enter the DNA sequence to be transcribed:"<<endl;
                cin>>first;
                while(!isValidStrand(first)){
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cout<<"Enter the DNA sequence to be transcribed:"<<endl;
                    cin>>first;
                }
                cout<<"The transcribed DNA is: ";
                transcribeDNAtoRNA(first);
                break;
            case 5:
                cout<<"Enter the DNA sequence:"<<endl;
                cin>>first;
                while(!isValidStrand(first)){
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cout<<"Enter the DNA sequence:"<<endl;
                    cin>>first;
                }
                cout<<"The reverse complement is: ";
                reverseComplement(first);
                break;
            case 6:
                cout<<"Enter the DNA sequence:"<<endl;
                cin>>first;
                while(!isValidStrand(first)){
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cout<<"Enter the DNA sequence:"<<endl;
                    cin>>first;
                }
                cout<<"The extracted reading frames are: "<<endl;
                getCodingFrames(first);
                break;
            case 7:
                cout<<"Exiting program."<<endl;
                break;
            default:
                cout<<"Invalid input. Please select a valid option."<<endl;
                break;
        }
    }
}
