use glium::winit::application::ApplicationHandler;
use glium::winit::event::WindowEvent;
use glium::winit::event_loop::{ActiveEventLoop, EventLoop};
use glium::winit::window::WindowId;
use glium::Surface;

struct Application {
    counter: u64,
}

impl ApplicationHandler for Application {
    fn resumed(&mut self, _: &ActiveEventLoop) {
        println!("resumed");
    }

    fn window_event(&mut self, event_loop: &ActiveEventLoop, _: WindowId, event: WindowEvent) {
        match event {
            WindowEvent::CloseRequested => {
                println!("Exiting");
                event_loop.exit();
            }
            _ => {
                println!("received {}", self.counter);
                self.counter += 1;
            }
        }
    }
}

fn main() {
    let event_loop = EventLoop::builder().build().expect("event loop building");
    let (_window, display) = glium::backend::glutin::SimpleWindowBuilder::new().build(&event_loop);

    let mut frame = display.draw();
    frame.clear_color(0.0, 0.0, 1.0, 1.0);
    frame.finish().unwrap();

    let _ = event_loop.run_app(&mut Application { counter: 0 });
}
