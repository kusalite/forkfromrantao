var deviceID    = "340025001647343337363432";
var accessToken = "362761d3b8d4980d024c05ace52781d454295a95";

$(document).foundation();

$( document ).ready(function() {
    $("#deviceIDInput").val(  deviceID );
    $("#accessTokenInput").val(  accessToken );
	
	loadSpreadsheet(1);
	
	listWorksheets();
	
	$('[data-slider]').on('changed.zf.slider', function(){
	    var value = $("#data-slider-hidden").attr('value');
		//alert( value );
		setTimeForShake( value );
		
	});
	
	$( "#shakeButton" ).on('click', function(){
	    shakeIt();
	});


    var source = new EventSource("https://api.particle.io/v1/events?access_token=" + accessToken );
    if (typeof(EventSource) !== "undefined") {
        console.log("SSE is Supported!");
    } else {
        console.log("SSE is NOT Supported");
    }
    console.log("Done");
    source.addEventListener('com.db/8ball/selection', function (e) {
        console.log(e)
        var obj = jQuery.parseJSON(e.data);
        //console.log(obj)
		var newListItem = $( "<li>" + obj.data + " <span>" + obj.published_at + "</span> </li>" )
        $("#history-list ul").append( newListItem );
    }, false);
	
	
	
	
	
});

function listWorksheets(){
	
}

function switchToSpreadSheet( index ){
	loadSpreadsheet( index );
	
	setSheet( index );
}

function loadSpreadsheet( index ){
	
	var ds = new Miso.Dataset({
	  importer : Miso.Dataset.Importers.GoogleSpreadsheet,
	  parser : Miso.Dataset.Parsers.GoogleSpreadsheet,
	  key : "1TgbQRTXTUFpo0YPES0bFOt2D88zkdcKl8W5xSF2mcFw",
	  worksheet : "" + index
	});

	ds.fetch({ 
	  success : function() {
	   
	    // empty it 
		$("#data-list").html("");
		  
		var firstCol = ds.columnNames()[0];
		
		ds.each(function(row, rowIndex) {
			var newListItem = $( "<li>" + row[firstCol] + "</li>" )
	        $("#data-list").append( newListItem );
			
			 
		});
		
	  },
	  error : function() {
	    log("Are you sure you are connected to the internet?");
	  }
	});
}


function handleDeviceIDChange(){
  deviceID = $("#deviceIDInput").val().trim();
  return ;
}

function handleAccessTokenChange(){
  accessToken = $("#accessTokenInput").val().trim();
  return ;
}

function setSheet( value ) {
  var requestURL = "https://api.particle.io/v1/devices/" +deviceID + "/setList/";
	$.post( requestURL, { params: value, access_token: accessToken });
}


function shakeIt() {
  var requestURL = "https://api.particle.io/v1/devices/" +deviceID + "/shake/";
	$.post( requestURL, { params: "1", access_token: accessToken });
}


function setTimeForShake( value ) {
  var requestURL = "https://api.particle.io/v1/devices/" +deviceID + "/setWaitTime/";
	$.post( requestURL, { params: value, access_token: accessToken });
}


