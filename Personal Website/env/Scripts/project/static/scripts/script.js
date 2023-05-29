var table = document.getElementsByClassName("dataframe");
for (var i = 1, row; row = table[0].rows[i]; i++) {
 
          var line1 = row.cells[3].innerHTML.slice(1);
          var line2 = row.cells[4].innerHTML.slice(1);
          line1 = "-" + line1
	    line2 = "-" + line2
	    console.log(line1)
	    console.log(line2)
          var num = parseInt(line1, 10);
	    var num2 = parseInt(line2, 10);
	    console.log(num)
	    console.log(num2)
	    if(num > num2){
		num = num2;
		}
	    if (num < -139) {
		row.style.backgroundColor = "LimeGreen"; 
          }else {
		row.style.backgroundColor = "#fc5226"; } 
          
}    

 