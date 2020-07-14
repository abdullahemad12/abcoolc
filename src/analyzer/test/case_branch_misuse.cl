class Main {
	x : Int <- 1;
	
	main() : Int {
		1 
	};

	y(x : Int) : Int {
		case x of 
			y : Int => y;
			z : String => ~1;
			y : Bool => 2;
			y : A => 3;
			self : Int => 4;
		esac
	};

};
