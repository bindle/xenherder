
function xenherder_init()
{
   // adds table sorting using JQuery/tablesorter
   // overrides sort function so that empty cells
   // are always evaluated as -1
   $.tablesorter.formatInt = function (s)
   {
      var i = parseInt(s);
      return (isNaN(i)) ? -1 : i;
   };
   $.tablesorter.formatFloat = function (s)
   {
      var i = parseFloat(s);
      return (isNaN(i)) ? -1 : i;
   };
   $("table").tablesorter();

   document.getElementById('javascript_warning').innerHTML = '';

   return;
}


/* for other browsers */
window.onload = xenherder_init;

/* end of JavaScript */