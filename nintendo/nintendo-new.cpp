
#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>

using namespace std;

int main()
{
  int size;

  cin >> size;

  unsigned int* a = new unsigned int[size / 16]; // <- input tab to encrypt
  unsigned int* b = new unsigned int[size / 16]; // <- output tab
 
  for (int i = 0; i < size / 16; i++) {   // Read size / 16 integers to a
    cin >> hex >> a[i];
  }

  for (int i = 0; i < size / 16; i++) {   // Write size / 16 zeros to b
    b[i] = 0;
  }	

  ofstream myfile;
  myfile.open("test.txt");

  int zercounter = 0;
  int onecounter = 0;

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) {
      myfile << "i = " << i << " j = " << j << endl;
      b[(i + j) / 32] ^= ( (a[i / 32] >> (i % 32)) &
		       (a[j / 32 + size / 32] >> (j % 32)) & 1 ) << ((i + j) % 32);   // Magic centaurian operation
      
      // result of (i + j)/32
      myfile << "(" << i << " + " << j << ")/32: " << (i + j)/32 << endl;
      // result of (i + j % 32), this is the number of bits that the result of anding a[0] and a[1] is shifted
      myfile << "(" << i << " + " << j << ") % " << "32): " << (i + j) % 32 << endl;
      // result of (a[i/32] >> (i % 32))
      myfile << "(" << "a[" << i/32 << "]) >> (" << i % 32 << "): " << std::bitset<32>(a[i / 32] >> (i % 32)).to_string() << endl;
      // result of (a[j/32 + size/32] >> (j % 32)) & 1
      myfile << "((" << "a[" << j/32 + size/32 << "] >> (" << j % 32 << ")) & 1:" << bitset<32>((a[j / 32 + size / 32] >> (j % 32)) & 1).to_string() << endl;
      // last two lines anded together and shifted by (i % j) % 32
      myfile << bitset<32>(((a[j / 32 + size / 32] >> (j % 32)) & 1) << ((i + j) % 32)).to_string() << endl; 
      myfile << endl;

      if ((i + j)/32 == 0) {
        zercounter++;
      } else {
        onecounter++;
      }
  }

  myfile << "zer counter: " << zercounter << endl;
  myfile << "one counter: " << onecounter << endl;
  myfile.close();

  for(int i = 0; i < size / 16; i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << setfill('0') << setw(8) << hex << b[i];       // print result
  }
  cout << endl;

 /* 
    Good luck humans     
 */
  return 0;
}
