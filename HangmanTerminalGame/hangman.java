import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;

class hangman {
  static String guess = "";
  static String guesses = "";
  static String alphabet = "abcdefghijklmnopqrstuvwxyz";
  static Scanner userGuess = new Scanner(System.in);

  public static void main(String args[])
    {
      String answer = "";
      try {
      File words = new File("words.txt");
      Scanner wordScanner = new Scanner(words);
      Random random = new Random();
      int randomInt = random.nextInt(849); //Set randomInt to a random integer 0 to 848 inclusive.
      while(randomInt == 0) //This while loop will make sure randomInt is not set to 0.
      {
      randomInt = random.nextInt(849);
      }
      for(int i = 0; i < randomInt; i++) //loop randomInt times in order to get the word on the randomInt line of words.txt. Set this word to be the answer, which is the word the player will try to guess.
	  {
      if (wordScanner.hasNextLine()){
	      answer = wordScanner.nextLine();
      }
	  }
      }
      catch (FileNotFoundException error) {
      System.out.println("An error occurred.");
    }

      int counter = 0;
      String dashes = "";
      for(int i = 0; i < answer.length(); i++)
      {
        dashes = dashes + "_";
      }
      String response = dashes; //initialize what the word looks like before the player makes any guesses with all dashes for each letter in the word.
      System.out.println("Welcome To Hangman. A word has been chosen. You may now guess any single letter. This is your word where each dash represents a letter: " + dashes);
      char[] output = dashes.toCharArray();
      while(counter < 6) //make sure player is under alloted amount of strikes.
      {
            getGuess(); //query the player for a valid guess.
            guesses = guesses + guess; //add the player's guess to a list of their previous guesses.
            if (answer.indexOf(guess) != -1) //check if the guess is correct by seeing if it is in the answer.
            {
            for(int i = 0; i < guesses.length(); i++) //If the guess is correct loop to fill in the player's correct guesses at the proper positions in the answer word within the output char array.
            {
              int index = answer.indexOf(guesses.charAt(i));
              while (index >= 0)
              {
                output[index] = guesses.charAt(i);
                index = answer.indexOf(guesses.charAt(i), index+1);
              }
            }
            response = String.valueOf(output); //Update the string showing what the answer word looks like with what the player has correctly guessed so far.
            strike(counter);  //call strike() to print out what the current hangman looks like depending on how many strikes the player has.
	    System.out.println("That is a correct guess.");
           }
           else //This else runs if the player's guess was wrong.
           {
             counter++; //increment the counter which is how many strikes the player has.
             strike(counter); //call strike() to print out what the current hangman looks like depending on how many strikes the player has.
             System.out.println("That is a strike.");
           }
           if (counter < 6) //check if player lost or not.
           {
             if (response.indexOf("_") == -1) //check if player won.
             {
               counter = 6;
               System.out.println("This is what you have uncovered with your current guesses: " + response + "\nYay!! You discovered the word! You win!!!");
             }
             else
             {
            System.out.println("This is what you have uncovered with your current guesses: " + response + "\nNow guess again");
          }
           }
           else {
             System.out.println("This is what you have uncovered with your current guesses: " + response + "\nUh oh too many wrong guesses you lose!!! The word you were trying to solve for was: " + answer);
           }

      }


    }

    public static void getGuess() {
      guess = userGuess.nextLine(); //get the player's next guess.
      if (guess.length() > 1) //check if guess is a single letter.
      {
        System.out.println("That is not a single letter. Try again!");
        getGuess();
      }
      else if (alphabet.indexOf(guess) == -1) //check if guess is proper alphabet letter.
      {
        System.out.println("That is not a letter. Try again!");
        getGuess();
      }
      else if (guesses.indexOf(guess) != -1) //check if the guess has already been guessed.
      {
        System.out.println("This is an invalid guess. Either you already guessed that letter or you did not guess a letter. Try again!");
        getGuess();
      }

    }

    public static void strike(int strikes) { //This method looks at how many strikes the player has and prints out the appropriate hangman image dependent on how many strikes the player has.
        if (strikes == 0)
        {
          System.out.println("   ______________    ");
          System.out.println("   |            |    ");
          System.out.println("   |                 ");
          System.out.println("   |                 ");
          System.out.println("   |                 ");
          System.out.println("   |                 ");
          System.out.println("   |                 ");
          System.out.println("   |                 ");
        }
        else if (strikes == 1)
        {
          System.out.println("   ______________    ");
          System.out.println("   |            |    ");
          System.out.println("   |          (   )  ");
          System.out.println("   |                 ");
          System.out.println("   |                 ");
          System.out.println("   |                 ");
          System.out.println("   |                 ");
          System.out.println("   |                 ");
        }
        else if (strikes == 2)
        {
          System.out.println("   ______________    ");
          System.out.println("   |            |    ");
          System.out.println("   |          (   )  ");
          System.out.println("   |            |    ");
          System.out.println("   |            |    ");
          System.out.println("   |                 ");
          System.out.println("   |                 ");
          System.out.println("   |                 ");
        }
        else if (strikes == 3)
        {
          System.out.println("   ______________    ");
          System.out.println("   |            |    ");
          System.out.println("   |          (   )  ");
          System.out.println("   |        ----|    ");
          System.out.println("   |            |    ");
          System.out.println("   |                 ");
          System.out.println("   |                 ");
          System.out.println("   |                 ");
        }
        else if (strikes == 4)
        {
          System.out.println("   ______________    ");
          System.out.println("   |            |    ");
          System.out.println("   |          (   )  ");
          System.out.println("   |        ----|----");
          System.out.println("   |            |    ");
          System.out.println("   |                 ");
          System.out.println("   |                 ");
          System.out.println("   |                 ");
        }
        else if (strikes == 5)
        {
          System.out.println("   ______________    ");
          System.out.println("   |            |    ");
          System.out.println("   |          (   )  ");
          System.out.println("   |        ----|----");
          System.out.println("   |            |    ");
          System.out.println("   |           /     ");
          System.out.println("   |          /      ");
          System.out.println("   |                 ");
        }
        else if (strikes == 6)
        {
          System.out.println("   ______________    ");
          System.out.println("   |            |    ");
          System.out.println("   |          (   )  ");
          System.out.println("   |        ----|----");
          System.out.println("   |            |    ");
          System.out.println("   |           / \\  ");
          System.out.println("   |          /   \\ ");
          System.out.println("   |                 ");
        }

    }




}
