var qpew = function(e){
	qprint(' Pew !!! '+qplus(e.health, 44)+' '+e.health);
	if (e.health < 120)
		e.health = e.health + 5;
};
