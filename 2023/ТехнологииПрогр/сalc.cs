/*
Написать консольное приложение калькулятор, которое будет реализовывать принципы ООП
Этапы:
Сделать базовый класс калькулятор, который будет реализовывать базовые функционал
Создать 3 дочерних класса от базового класса калькулятор, которые будут иметь базовый функционал калькулятора, но при этом уметь делать другие специфические штуки (Например функционал, инженерного калькулятора)
*/

using System;

class Program {
	class Calc {
		public double Count(double a, double b, string sign){
			double res = 0;
			switch(sign)
			{
			case "+":res = a + b; break;
			case "-":res = a - b; break;
			case "*":res = a * b; break;
			case "/":res = a / b; break;
			default:break;
			}
			return(res);
		}
		public void ShowWorknigMenu(){
			Console.WriteLine("To go back to menu print 'r'");
			Console.WriteLine("WARNING: Spaces matters!");
			Console.WriteLine("Write smth like 'a + b'");			
		}
		public void ReadMath(){
			double a = 0; double b = 0;
			string sign;	

			while(true)
			{
				string[] temp = Console.ReadLine().Split(' ');
				if(temp.Length==1)
				{
					if(temp[0]=="r") return;
				}
				else{			
					a = int.Parse(temp[0]);
					sign = temp[1];
					b = int.Parse(temp[2]);
					Console.WriteLine(Count(a,b,sign));
				}
			}
		}
		public void ShowMainMenu(){
			Console.WriteLine("Menu:");
			Console.WriteLine("\t" + "mode - q");
			Console.WriteLine("\t" + "use - w");
			Console.WriteLine("\t" + "show menu - s");
			Console.WriteLine("\t" + "exit - e");
		}
		public int Menu(bool show){
			if(show) ShowMainMenu();
			string[] temp = Console.ReadLine().Split(' ');	
			foreach(string str in temp)
				switch(str){
					case "q": break;
					case "w": ReadMath(); break;
					case "s": ShowMainMenu(); break;
					case "e": return 1; 
					default: break;
				}
			return 0;
		}
	}
	class ExtClac : Calc{
		public double Count(string sign, string param){
			double res = 0;
			switch(sign)
			{
			/*case "pow":res = a + b; break;
			case "-":res = a - b; break;
			case "*":res = a * b; break;
			case "/":res = a / b; break;*/
			default:break;
			}
			return(res);
		}
		public new void ShowWorknigMenu(){
			
			Console.WriteLine("Or write smth like 'pow a,b'");
		}
	}
	
	public static void operateSimpleCalc(){
		Calc prog = new Calc();
		int a = 0;
		while(a==0){
			a = prog.Menu(true);
		}
	}
/*	public static void operateExtendedCalc(){
		ExtClac prog = new ExtClac();
		int a = 0;
		while(a==0){
			a = prog.Menu(true);
		}
	}*/
	public static void Main (string[] args) {
		Console.WriteLine("Simple = 0, Extended = 1, Engineer = 2");
		Console.WriteLine("Choose calc mode \n");
		var mode = int.Parse(Console.ReadLine());

		switch(mode){
		case 0: operateSimpleCalc(); break;
		//case 1: operateExtendedCalc(); break;
		case 2: break;
		default: break;
		}
	}
}
