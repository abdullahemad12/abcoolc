class Main inherits IO {
   aa : A;
   k : Int <- 3 * 5 + 5;
   a() : Object {
   	case "hello" of
   		x : String  => out_int(3 + 4 + 9 + k);
   	esac
   };
   main(): Object {
	a()
   };
};


class A 
{

};
class B
{
};
