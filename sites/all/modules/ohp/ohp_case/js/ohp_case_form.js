// Author: Jordi Roda, Ernest Pastor, Filip Velickovski, Magí Lluch-Ariet  
// Barcelona Digital Technology Centre, 2014 
// 
// Open Health Practice is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Open Health Practice is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

(function($){
	$(document).ready(function(){
		checkFormulas();
	});
}(window.jQuery));
	function checkFormulas(){
	  var field_formulas = Drupal.settings.field_formulas;
	  for (var key in field_formulas) {
	    var value = field_formulas[key];
	    if(value.indexOf("#DIVIDE")!=-1){
	      var array = value.split(",");
	      var a1 = document.querySelector("input[name='"+array[1].substring(1)+"']");
	      var a2 = document.querySelector("input[name='"+array[2].substring(1)+"']");
	      var a0 = document.querySelector("input[name='"+key+"']");
	      if (typeof a1 !== "undefined" && a1!=null && 
	    		  typeof a2 !== "undefined" && a2!=null &&
		    	  typeof a0 !== "undefined" && a0!=null) { 
	        var a1n = a1.value.replace(/\./g, '').replace(',', '.');
	        var a2n = a2.value.replace(/\./g, '').replace(',', '.');
	        if(isNumber(a1n) && isNumber(a2n)){
	          a0.value=(a1n/a2n).toFixed(2).replace(".", ",");
	        }else{
	          a0.value='';
	        }
	        fireOnChange(a0);
	      }
	    }else if(value.indexOf("#RANGE")!=-1){
		  var value2 = value.substring(7,value.length-1);
		  array = value2.split(",");
		  var type = document.querySelector("input[name='question_type_"+array[0].substring(1)+"']");
		  if(type.value==='VERTICAL_RADIO' || type.value==='HORIZONTAL_RADIO'){
	        a1= document.querySelector("select[name='"+array[0].substring(1)+"']");
		  }else{
			a1= document.querySelector("input[name='"+array[0].substring(1)+"']");
		  }
	      var a0 = document.querySelector("input[name='"+key+"']");
	      var min = array[1];
	      var max = array[2];
	      var val1 = +array[3];
	      var val2 = +array[4];
	      var val3 = +array[5];
	      if (typeof a1 !== "undefined" && a1!=null &&
	          typeof a0 !== "undefined" && a0!=null) {
	    	var a1n = +(a1.value.replace(/\./g, '').replace(',', '.'));
	    	if(a1n<min){
	    	  a0.value=val1;
	    	}else if(a1n>=min && a1n<=max){
	    	  a0.value=val2;
	    	}else{
	    	  a0.value=val3;
	    	}
	    	fireOnChange(a0);
    	  }
	    }
	  }
	}
	function fireOnChange(a0) {
	    var event; // The custom event that will be created
	    if (document.createEvent) {
    	  event = document.createEvent("HTMLEvents");
    	  event.initEvent("change", true, true);
	    } else {
		  event = document.createEventObject();
		  event.eventType = "change";
	    }
	    event.eventName = "change";
	    if (document.createEvent) {
    	  a0.dispatchEvent(event);
	    } else {
		  a0.fireEvent("on" + event.eventType, event);
		}
	}
	function isNumber(n) {
	  return !isNaN(parseFloat(n)) && isFinite(n);
	}
