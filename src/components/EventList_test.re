open Jest;

open Utils;

open Expect;

Enzyme.configureEnzyme(Enzyme.react_16_adapter());

let shallow = Enzyme.shallow;
let sampleOnAddEvent = (_event) => { () };
let setup = (~name="", ~events=[], ~onAddEvent=sampleOnAddEvent,  ()) => Enzyme.shallow(<EventList events name onAddEvent/>);

describe(
  "EventList Component",
  () => {
    test("component renders", () => setup() |> Enzyme.exists |> expect |> toBe(true));
    test("takes a name and renders it in a header", () => {
      let name = "testing";
      let textElement = textEl(name);
      shallow(<EventList name onAddEvent=sampleOnAddEvent />) |> Enzyme.contains(textElement) |> expect |> toBe(true);
      });
    test(
      "renders a list of events",
      () => {
        let name = "crazy name";
        let l : list(Event.t) = [{ name: name }];
        setup(~events=l, ()) |> Enzyme.html |> expect |> toContainString(name)
      });
    test("clicking on add button triggers onAddEvent", () => {
      let clickFired = ref(false);
      let onAddEvent = (_event) => clickFired := true;
      shallow(<EventList onAddEvent name="test" />) |> Enzyme.find(".add-new-event") |>
      Enzyme.simulate("click");
      clickFired^ |> expect |> toBe(true);
    });

  });

