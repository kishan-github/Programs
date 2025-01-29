/******************************************************************************

We have a string str, find the max number of vowels in a substring of size k.

*******************************************************************************/
using System;
using System.Linq;
class HelloWorld {
  static void Main() {
    string str = "qwrtypsdfghjklzxvbnm";
    int k = 5;
    
    Console.WriteLine("Number of vowels = " + maxNumberOfVowels(str, k));
  }
  
  static int maxNumberOfVowels(string s, int k)
  {
      if (s == null || s.Length == 0 || s.Length < k)
        return 0;
    
      string vowels = "aeiouAEIOU";
      int maxVowels = s.Substring(0, k).Count(c => vowels.Contains(c));
      int numberOfVowels = maxVowels;
      
      for (int i = 1; i < s.Length - k; i++)
      {
          if (vowels.Contains(s[i - 1]))
            numberOfVowels--;
        
          if (vowels.Contains(s[i + k]))
            numberOfVowels++;
            
          if (numberOfVowels > maxVowels)
            maxVowels = numberOfVowels;
      }
      
      return maxVowels;
  }
}
