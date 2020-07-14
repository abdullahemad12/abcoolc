class Main {
	x : Int <- 1;
	
	main() : Int {
		1 
	};

	y(x : Int) : Int {
		case x of 
			y : Int => y;
			z : Int => ~1;
			y : Int => 2;
			y : String => 3;
		esac
	};

};
