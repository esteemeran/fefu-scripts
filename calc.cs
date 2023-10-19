//console calculator
using System;

class Program {
	enum CalcMode {Simple = 0, Extended, Engineer};
	class Calc {
		CalcMode mode = 0;
		
		public static void Count(double a, double b, string sign){
			double res = 0;
			switch(sign)
			{
			case "+":res = a + b; break;
			case "-":res = a - b; break;
			case "*":res = a * b; break;
			case "/":res = a / b; break;
			default:break;
			}
			Console.WriteLine(res);
		}
		public static void Read(double a, double b, string sign){
			Console.WriteLine("Write smth like 'a + b'");
			Console.WriteLine("Spaces matters!");
			string[] temp = Console.ReadLine().Split(' ');	
			a = int.Parse(temp[0]);
			sign = temp[1];
			b = int.Parse(temp[2]);
		}
		public static void Menu(string sign){
			Console.WriteLine("Menu:");
			Console.WriteLine("\t" + "mode - q");
			Console.WriteLine("\t" + "use - w");
			Console.WriteLine("\t" + "exit - e");
		}
	}
	public static void Main (string[] args) {
		Console.WriteLine("Simple = 0, Extended = 1, Engineer = 2");
		Console.WriteLine("Choose calc mode \n");
		var mode = int.Parse(Console.ReadLine());
		
		var a = 0;
		var b = 0;
		string sign = "";
		CalcRead(a,b,sign);
		
		switch(mode)
		{
		case CalcMode.Simple: CalcCount(a, b, sign); break;
		case CalcMode.Extended:break;
		case CalcMode.Engineer:break;
		default:break;
		}		
  }
}
