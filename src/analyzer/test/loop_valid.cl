class Main {
	x : Int <- 10;
	main() : Int {
		while 0 < x loop
		{
			x <- x - 1;
		}
		pool
	};
};
