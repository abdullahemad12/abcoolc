class Main {
	x : Int <- 0;
	main() : Int {
		case x of
			x : Int => x;
			x : String => 2;
			y : Bool => 3;
		esac
	};
};
